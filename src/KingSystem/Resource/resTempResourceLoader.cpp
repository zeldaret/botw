#include "KingSystem/Resource/resTempResourceLoader.h"
#include <resource/seadResource.h>
#include <thread/seadThread.h>
#include "KingSystem/Resource/resArchiveWork.h"
#include "KingSystem/Resource/resResourceMgrTask.h"
#include "KingSystem/Resource/resSystem.h"
#include "KingSystem/Resource/resUnit.h"
#include "KingSystem/Utils/Debug.h"
#include "KingSystem/Utils/Thread/TaskThread.h"

namespace ksys::res {

TempResourceLoader::TempResourceLoader() = default;

TempResourceLoader::~TempResourceLoader() {
    unload();
}

void TempResourceLoader::unload() {
    const auto* unit = mHandle.getUnit();
    const auto& path = unit ? unit->getPath() : sead::SafeString::cEmptyString;
    sead::FormatFixedSafeString<256> message("(TempResourceLoader) アンロードします。: %s\n",
                                             path.cstr());
    util::PrintDebug(message);

    if (mFlags.isOn(Flag::IsRetryingLoad)) {
        stubbedLogFunction();
        mFlags.reset(Flag::IsRetryingLoad);
    } else if (returnFalse()) {
        stubbedLogFunction();
    }

    mFlags.reset(Flag::Loading);
    mHandle.requestUnload();

    if (mResource) {
        ResourceMgrTask::instance()->unloadSeadResource(mResource);
        mResource = nullptr;
    }

    if (mWork)
        mWork->setEvent();
}

bool TempResourceLoader::init(const InitArg& arg) {
    mWork = arg.work;
    return true;
}

bool TempResourceLoader::isLoading() const {
    return mFlags.isOn(Flag::Loading);
}

bool TempResourceLoader::isSuccess() const {
    return !isLoading() && mHandle.isSuccess();
}

bool TempResourceLoader::checkLoadStatus() const {
    return !isLoading() && mHandle.checkLoadStatus();
}

void TempResourceLoader::requestLoad(LoadArg& arg) {
    if (!arg.use_handle)
        return;

    updateFlagsBeforeLoadingStarts();
    mPath = arg.load_req.mPath;
    mLoadArg = arg;
    mLoadArg.load_req.mPath = mPath;
    arg.load_req.mArena = mWork->getArena();
    mHandle.requestLoad(arg.load_req.mPath, &arg.load_req);
    if (returnFalse())
        stubbedLogFunction();
}

sead::DirectResource* TempResourceLoader::getResourceForLoadRequest(Context* context) {
    if (!mLoadArg.use_handle || !mHandle.requestedLoad() || mHandle.hasParsedResource() ||
        !mHandle.isReadyOrNeedsParse()) {
        return nullptr;
    }

    mHandle.parseResource(context);

    if (!mHandle.isSuccess()) {
        if (mHandle.getStatus() != Handle::Status::_3) {
            mFlags.reset(Flag::Loading);
            sead::FormatFixedSafeString<256> message(
                "(TempResourceLoader) メモリ不足以外のエラーでした。: %s(%d)\n",
                mLoadArg.load_req.mPath.cstr(), s32(mHandle.getStatus()));
            util::PrintDebug(message);
            resetRetryFlag();
            return nullptr;
        }

        if (!mLoadArg.retry_on_failure) {
            mFlags.reset(Flag::Loading);
            sead::FormatFixedSafeString<256> message(
                "(TempResourceLoader) ロード失敗しました。: %s\n", mLoadArg.load_req.mPath.cstr());
            util::PrintDebug(message);
            resetRetryFlag();
            return nullptr;
        }

        setRetryFlag();
        mLoadArg.load_req.mArena = mWork->getArena();
        mHandle.requestLoad(mLoadArg.load_req.mPath, &mLoadArg.load_req);
        return nullptr;
    }

    mFlags.reset(Flag::Loading);
    sead::FormatFixedSafeString<256> message("(TempResourceLoader) ロードに成功しました。: %s\n",
                                             mLoadArg.load_req.mPath.cstr());
    util::PrintDebug(message);
    resetRetryFlag();
    return mHandle.getResource();
}

sead::DirectResource* TempResourceLoader::load(TempResourceLoader::LoadArg& arg) {
    updateFlagsBeforeLoadingStarts();

    const auto* current_thread = sead::ThreadMgr::instance()->getCurrentThread();
    bool is_on_res_thread = false;
    is_on_res_thread |= current_thread == ResourceMgrTask::instance()->getResourceMemoryThread();
    is_on_res_thread |= current_thread == ResourceMgrTask::instance()->getResourceLoadingThread();
    if (is_on_res_thread)
        arg.use_handle = false;

    while (true) {
        if (returnFalse())
            stubbedLogFunction();

        bool use_handle = arg.use_handle;
        auto* arena = mWork->getArena();
        if (use_handle) {
            arg.load_req.mArena = arena;
            mHandle.load(arg.load_req.mPath, &arg.load_req);

            if (mHandle.isSuccess())
                break;

            if (mHandle.getStatus() != Handle::Status::_3) {
                mFlags.reset(Flag::Loading);
                sead::FormatFixedSafeString<256> message(
                    "(TempResourceLoader) メモリ不足以外のエラーでした。: %s(%d)\n",
                    arg.load_req.mPath.cstr(), s32(mHandle.getStatus()));
                util::PrintDebug(message);
                resetRetryFlag();
                return nullptr;
            }
        } else {
            ResourceMgrTask::DirectLoadArg load_arg{};
            load_arg.heap = arena->getHeap();
            load_arg.req._21 = false;
            load_arg.req._22 = true;
            load_arg.req.mPath = arg.load_req.mPath;
            load_arg.req.mAocFileDevice = arg.load_req.mAocFileDevice;
            load_arg.req.mLoadDataAlignment = arg.load_req.mLoadDataAlignment;
            load_arg.req.mEntryFactory = arg.load_req.mEntryFactory;
            load_arg.req._20 = false;
            load_arg.req.mRequester = "TempResourceLoader";

            if (arena->getHeap()->isLockEnabled())
                arena->getHeap()->getCriticalSection().lock();

            mResource = ResourceMgrTask::instance()->load(load_arg);

            if (arena->getHeap()->isLockEnabled())
                arena->getHeap()->getCriticalSection().unlock();

            if (mResource) {
                mFlags.reset(Flag::Loading);
                return mResource;
            }
        }

        if (!arg.retry_on_failure) {
            mFlags.reset(Flag::Loading);
            sead::FormatFixedSafeString<256> message(
                "(TempResourceLoader) ロード失敗しました。: %s\n", arg.load_req.mPath.cstr());
            util::PrintDebug(message);
            resetRetryFlag();
            return nullptr;
        }

        setRetryFlag();
        if (!mWork->waitForEvent(arg.ms_between_attempts)) {
            mFlags.reset(Flag::Loading);
            return nullptr;
        }
    }

    mFlags.reset(Flag::Loading);
    sead::FormatFixedSafeString<256> message("(TempResourceLoader) ロードに成功しました。: %s\n",
                                             arg.load_req.mPath.cstr());
    util::PrintDebug(message);
    resetRetryFlag();
    return mHandle.getResource();
}

sead::DirectResource* TempResourceLoader::getResource() const {
    if (mHandle.getResource())
        return mHandle.getResource();
    return mResource;
}

Handle::Status TempResourceLoader::getHandleStatus() const {
    return mHandle.getStatus();
}

sead::FileDevice* TempResourceLoader::getHandleFileDevice() const {
    if (mHandle.isSuccess())
        return mHandle.getUnit()->getLoadArg().device;
    return nullptr;
}

u32 TempResourceLoader::getWorkHeapSize() const {
    return mWork ? mWork->getHeapSize() : 0;
}

}  // namespace ksys::res
