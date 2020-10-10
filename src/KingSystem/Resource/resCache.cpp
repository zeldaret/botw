#include "KingSystem/Resource/resCache.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/Resource/resCacheCriticalSection.h"
#include "KingSystem/Resource/resControlTask.h"
#include "KingSystem/Resource/resResourceMgrTask.h"
#include "KingSystem/Resource/resSystem.h"
#include "KingSystem/Utils/Debug.h"

namespace ksys::res {

Cache::Cache() = default;

void Cache::init() {}

ResourceUnit* Cache::findUnit(const util::StrTreeMapNode::KeyType& key) const {
    auto lock = sead::makeScopedLock(gCacheCriticalSection);
    ResourceUnitMapNode* node = mMap.find(key);
    return node ? node->getUnit() : nullptr;
}

Handle::Status Cache::loadResource(const ControlTaskData& data) {
    auto* handle = data.mResHandle;
    if (handle->isLinked()) {
        stubbedLogFunction();
        return Handle::Status::_8;
    }

    {
        const auto path = data.mResLoadReq.mPath;
        ResourceUnit* unit = data.mPackResUnit;
        auto lock = sead::makeScopedLock(gCacheCriticalSection);
        bool remove_from_cache_if_needed = true;
        if (!unit) {
            unit = findUnit(path);
            remove_from_cache_if_needed = [&] {
                if (!unit)
                    return false;

                if (unit->mStatusFlags.isOn(ResourceUnit::StatusFlag::_80)) {
                    unit->removeFromCache();
                    if (returnFalse())
                        stubbedLogFunction();
                    return false;
                }

                if (unit->isStatusFlag10000Set()) {
                    unit->removeFromCache();
                    return false;
                }

                if (unit->isStatus0()) {
                    sead::FormatFixedSafeString<256> message("↓↓↓\nリソース名 : %s\n↑↑↑\n",
                                                             path.cstr());
                    util::PrintDebug(message);
                    return false;
                }

                return true;
            }();
        }

        if (remove_from_cache_if_needed) {
            const bool removed = unit->removeTask3FromQueue();
            if (unit->isLinkedToResourceMgr()) {
                unit->removeFromCache();
            } else if (removed) {
                unit->updateStatus();
                unit->attachHandle(handle);
                return unit->getRefCount() == 1 ? Handle::Status::_6 : Handle::Status::_5;
            }
        }
    }

    if (data.mHasResLoadReq)
        return Handle::Status::_8;

    ResourceUnit* result;

    {
        sead::FixedSafeString<128 + 7> new_path;
        sead::SafeString path = data.mResLoadReq.mPath;

        bool set_flag_4 = false;
        if (data.mResLoadReq.mLoadCompressed) {
            auto it = data.mResLoadReq.mPath.rfindIterator(".");
            if (it.getIndex() == -1)
                return Handle::Status::_1;

            ++it;
            sead::SafeString extension;
            extension = &*it;
            set_flag_4 = ResourceMgrTask::instance()->dropSFromExtensionIfNeeded(
                data.mResLoadReq.mPath, new_path, it.getIndex() - 1, extension);
        }

        if (!new_path.isEmpty())
            path = new_path;

        ResourceUnit::InitArg init_arg(false, false, set_flag_4, data.mResLoadReq._26,
                                       data.mResLoadReq._28, handle, this, nullptr, nullptr,
                                       &data.mResLoadReq, data.mResLoadReq.mArena,
                                       data.mResLoadReq.mBufferSize, path);

        ResourceMgrTask::GetUnitArg arg;
        arg.unit_init_arg = &init_arg;
        arg.arena = data.mResLoadReq.mArena;

        result = ResourceMgrTask::instance()->clearCachesAndGetUnit(arg);
    }

    if (!result)
        return Handle::Status::_3;

    {
        auto lock = sead::makeScopedLock(gCacheCriticalSection);
        mMap.insert(&result->mMapNode);
        result->setIsLinkedToCache(true);
    }

    u8 lane_id = 0xff;
    if (data.mResLoadReq._c <= 2) {
        const bool x = result->mStatusFlags.isOn(ResourceUnit::StatusFlag::LoadFromArchive);
#ifdef MATCHING_HACK_NX_CLANG
        // This makes absolutely no sense at all, but this prevents InstCombine from
        // turning (x & 0x20) >> 5 into (x >> 5) & 1 by adding a fake-use.
        // LLVM (4.0.1 at least) doesn't do anything with this piece of information
        // so the conditional still works fine.
        __builtin_assume(x);
#endif
        lane_id = 2 * data.mResLoadReq._c + (x ? 1 : 2);
    }

    ResourceUnit::RequestInitLoadArg load_arg;
    load_arg.lane_id = lane_id;
    load_arg.has_handle = data.mResLoadReq._8;
    result->requestInitLoad(load_arg);
    return Handle::Status::_7;
}

void Cache::eraseUnit(ResourceUnit* unit) {
    auto lock = sead::makeScopedLock(gCacheCriticalSection);
    if (unit->isLinkedToCache()) {
        mMap.erase(unit->getCacheKey());
        unit->setIsLinkedToCache(false);
    }
}

void Cache::removeUnitAndClearCache_(ResourceUnit* unit) {
    ResourceMgrTask::ClearCacheArg arg{unit};
    unit->mStatusFlags.reset(ResourceUnit::StatusFlag::_20000);
    if (unit->isStatusFlag8000Set()) {
        ResourceMgrTask::instance()->eraseUnit(unit);
        ResourceMgrTask::instance()->clearCache(arg);
    }
}

namespace detail::cache {
struct ForEachContextData {
    ForEachContextData() = default;
    virtual ~ForEachContextData() = default;
    virtual void invoke(const util::StrTreeMapKey&, ResourceUnit*& value) {
        (value->getCache()->*fn)(value);
    }

    void (Cache::*fn0)(ResourceUnit* unit);
    void (Cache::*fn)(ResourceUnit* unit);
};
KSYS_CHECK_SIZE_NX150(ForEachContextData, 0x28);

struct ForEachContext {
    void deleteUnit(util::StrTreeMapNode* node_) {
        auto* node = static_cast<ResourceUnitMapNode*>(node_);
        data->invoke(node->key(), node->getUnit());
    }

    ForEachContextData* data;
};
KSYS_CHECK_SIZE_NX150(ForEachContext, 0x8);
}  // namespace detail::cache

void Cache::eraseUnits() {
    using namespace detail::cache;
    ForEachContextData data{};
    data.fn = &Cache::removeUnitAndClearCache_;
    auto lock = sead::makeScopedLock(gCacheCriticalSection);
    ForEachContext context{&data};
    sead::Delegate1<ForEachContext, util::StrTreeMapNode*> delegate{&context,
                                                                    &ForEachContext::deleteUnit};
    mMap.forEach(delegate);
}

}  // namespace ksys::res
