#include "KingSystem/Resource/resUnit.h"
#include <filedevice/seadArchiveFileDevice.h>
#include <resource/seadArchiveRes.h>
#include "KingSystem/Resource/resCache.h"
#include "KingSystem/Resource/resControlTask.h"
#include "KingSystem/Resource/resEntryFactory.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Resource/resResourceMgrTask.h"
#include "KingSystem/Resource/resSystem.h"

namespace ksys::res {

ResourceUnit::ResourceUnit(const InitArg& arg)
    : mArena(arg.arena), mLoadReqArena(arg.load_req->mArena), mLoadReqField68(arg.load_req->_68),
      mCache(arg.cache), mFileDevice(arg.load_req->mFileDevice),
      mLoadReqAllocSize(arg.load_req->_34), mAllocSize(arg.alloc_size), mPath(arg.path),
      mHeap(arg.heap) {
    init(arg);
}

ResourceUnit::ResourceUnit() = default;

bool ResourceUnit::init(const ResourceUnit::InitArg& arg) {
    mCacheFlags.makeAllZero();
    mFlags.makeAllZero();
    mStatusFlags.makeAllZero();
    mStatus = Status::_0;
    mArena = arg.arena;
    mArena1 = nullptr;
    mArena2 = nullptr;
    mLoadReqArena = arg.load_req->mArena;
    mArchiveRes = nullptr;
    mResource = nullptr;
    mLoadReqField68 = arg.load_req->_68;
    mCache = arg.cache;
    mFileDevice = arg.load_req->mFileDevice;
    mLoadReqAllocSize = arg.load_req->_34;
    mAllocSize = arg.alloc_size;
    mInfoAllocSize = 0;
    mRefCount.storeNonAtomic(0);
    mCounter.storeNonAtomic(0);
    mEvent.resetSignal();
    mLoadArg = {};
    mPath = arg.path;
    mHeap = arg.heap;

    if (arg.load_req->mPackHandle) {
        SimplePackedLoadRequest request;
        request._8 = true;
        request.mRequester = "ResourceUnit";
        request.mLaneId = 2;
        request.mPack = arg.load_req->mPackHandle;
        mArchiveRes = sead::DynamicCast<sead::ArchiveRes>(mArchiveResHandle.load("", &request));
    }

    mMapNode.key().setKey(mPath);

    mLoadArg.path = mPath;
    mLoadArg.instance_heap = nullptr;
    mLoadArg.instance_alignment = sizeof(void*);
    mLoadArg.load_data_heap = nullptr;
    mLoadArg.load_data_alignment = arg.load_req->mLoadDataAlignment;
    mLoadArg.load_data_buffer = nullptr;
    mLoadArg.load_data_buffer_size = arg.load_req->mBufferSize;
    mLoadArg.factory = arg.load_req->mEntryFactory;
    mLoadArg.device = arg.load_req->mAocFileDevice;
    mLoadArg.assert_on_alloc_fail = false;

    bool load_from_archive;
    if (sead::IsDerivedFrom<sead::ArchiveFileDevice>(mLoadArg.device))
        load_from_archive = true;
    else
        load_from_archive = arg.load_req->mPackHandle != nullptr;

    mStatusFlags.change(StatusFlag::BufferSizeIsNonZero, arg.load_req->mBufferSize != 0);
    mStatusFlags.change(StatusFlag::LoadFromArchive, load_from_archive);
    mStatusFlags.change(StatusFlag::LoadReqField24IsTrue, arg.load_req->_24);

    mFlags.change(Flag::_1, arg.set_flag_1);
    mFlags.change(Flag::_2, arg.set_flag_2);
    mFlags.change(Flag::_4, arg.set_flag_4);

#ifdef MATCHING_HACK_NX_CLANG
    mStatusFlags.change(StatusFlag::_20000,
                        arg.load_req_field_26 &&
                            !*static_cast<const volatile bool*>(&arg.load_req_field_28));
#else
    mStatusFlags.change(StatusFlag::_20000, arg.load_req_field_26 && !arg.load_req_field_28);
#endif
    mStatusFlags.change(StatusFlag::_40000, arg.load_req->_27);
    mStatusFlags.change(StatusFlag::HasHeap, arg.heap != nullptr);
    mStatusFlags.change(StatusFlag::_80000, arg.load_req_field_28);

    if (arg.handle) {
        arg.handle->setUnit(this);
        mRefCount.increment();
        mStatusFlags.reset(StatusFlag::NeedToIncrementRefCount);
    }

    {
        util::TaskDelegateSetter setter;
        mTask1.setDelegate(setter);
    }

    {
        util::TaskDelegateSetter setter;
        mTask2.setDelegate(setter);
    }

    if (mStatusFlags.isOn(StatusFlag::_80000)) {
        mRefCount.increment();
        mStatusFlags.reset(StatusFlag::NeedToIncrementRefCount);
        stubbedLogFunction();
    }

    return true;
}

ResourceUnit::~ResourceUnit() {
    unloadArchiveRes();
}

void ResourceUnit::unloadArchiveRes() {
    if (mArchiveRes) {
        mArchiveRes = nullptr;
        mArchiveResHandle.requestUnload();
    }
}

void ResourceUnit::attachHandle(Handle* handle) {
    handle->setUnit(this);
    mRefCount.increment();
    mStatusFlags.reset(StatusFlag::NeedToIncrementRefCount);
}

s32 ResourceUnit::getRefCount() const {
    return mRefCount;
}

ResourceUnit::Status ResourceUnit::getStatus() const {
    return mStatus;
}

static const ResourceUnit::Status sUnitStatusTransitionTable[] = {
    ResourceUnit::Status::_8,  ResourceUnit::Status::_11, ResourceUnit::Status::_11,
    ResourceUnit::Status::_14, ResourceUnit::Status::_14,
};

// NON_MATCHING: ldr + sxtw -> ldrsw
void ResourceUnit::updateStatus() {
    const s32 idx = mStatus;
    if (Status::_2 <= idx && idx <= Status::_6)
        mStatus = sUnitStatusTransitionTable[idx];
}

bool ResourceUnit::isTask1NotQueued() const {
    return mTask1.getStatus() == util::Task::Status::RemovedFromQueue;
}

bool ResourceUnit::isStatus0() const {
    return mStatus == Status::_0;
}

bool ResourceUnit::isTask1ActiveOrStatus7() const {
    if (!mTask1.isInactive())
        return true;
    if (isTask1NotQueued())
        return false;
    return mStatus == Status::_7;
}

bool ResourceUnit::isStatus1() const {
    return mStatus == Status::_1;
}

bool ResourceUnit::needsParse() const {
    auto* res = sead::DynamicCast<Resource>(mResource);
    if (mStatus != Status::_8 && mStatus != Status::_11)
        return false;
    return res && res->needsParse();
}

bool ResourceUnit::isStatus9_12_15() const {
    return mStatus == Status::_9 || mStatus == Status::_12 || mStatus == Status::_15;
}

// NON_MATCHING: branching for the second if
bool ResourceUnit::isParseOk() const {
    auto* ksys_res = sead::DynamicCast<res::Resource>(mResource);

    const auto status = mStatus.value();

    if (status == Status::_14)
        return true;

    if (status == Status::_8 && !ksys_res)
        return mResource != nullptr;

    if (status == Status::_8 && ksys_res)
        return !ksys_res->needsParse();

    return false;
}

bool ResourceUnit::isStatusFlag8000Set() const {
    return mStatusFlags.isOn(StatusFlag::NeedToIncrementRefCount);
}

bool ResourceUnit::isLinkedToResourceMgr() const {
    return mResMgrUnitListNode.isLinked();
}

size_t ResourceUnit::getHeapSize() const {
    return mHeap ? mHeap->getSize() : 0;
}

sead::Heap* ResourceUnit::getHeap() const {
    return mHeap;
}

bool ResourceUnit::isLinkedToCache() const {
    return mCacheFlags.isOn(CacheFlag::IsLinkedToCache);
}

void ResourceUnit::setIsLinkedToCache(bool linked) {
    mCacheFlags.change(CacheFlag::IsLinkedToCache, linked);
    if (returnFalse())
        stubbedLogFunction();
}

void ResourceUnit::removeFromCache() {
    if (mCache)
        mCache->eraseUnit(this);
    else
        stubbedLogFunction();
}

bool ResourceUnit::removeTask3FromQueue() {
    mTask3.removeFromQueue();
    return true;
}

void ResourceUnit::requestInitLoad(const RequestInitLoadArg& arg) {
    mStatus = Status::_7;

    util::TaskRequest req;
    req.mHasHandle = arg.has_handle;
    req.mSynchronous = false;
    req.mLaneId = arg.lane_id;
    req.mThread = ResourceMgrTask::instance()->getResourceMemoryThread();
    req.mDelegate = &ResourceMgrTask::instance()->getUnitInitLoadFn().fn;
    req.mUserData = this;
    req.mPostRunCallback = &ResourceMgrTask::instance()->getUnitInitLoadFn().cb;
    req.mName = mPath;
    mTask1.submitRequest(req);

    if (returnFalse2(sead::SafeString(mPath)))
        stubbedLogFunction();
}

bool ResourceUnit::waitForResourceAndParse(Context* context) {
    const auto adjust_heap_and_dec_ref = [&] {
        adjustHeapAndArena();
        if (mStatusFlags.isOn(StatusFlag::_80000)) {
            mRefCount.decrement();
            mStatusFlags.reset(StatusFlag::_80000);
            ksys::res::stubbedLogFunction();
        }
    };

    if (isParseOk())
        return true;

    if (mCounter.increment() >= 1) {
        mEvent.wait();
        if (mStatus != Status::_15 && mStatus != Status::_12)
            return true;
        ksys::res::stubbedLogFunction();
        return false;
    }

    mTask1.wait();
    bool set_status_12 = true;
    if (mResource) {
        auto* res = sead::DynamicCast<ksys::res::Resource>(mResource);
        if (!res || !res->needsParse()) {
            mEvent.setSignal();
            return true;
        }

        bool finish_parsing = mStatus != Status::_8;
        if (!finish_parsing) {
            auto* heap = mHeap;
            mStatus = Status::_10;
            if (context)
                res->setContext(context);

            if (res->parse(context, heap)) {
                mStatus = Status::_11;
                finish_parsing = true;
            } else {
                adjust_heap_and_dec_ref();
            }
        }

        if (finish_parsing) {
            mStatus = Status::_13;
            if (mResource) {
                bool ok = true;
                if (auto* ksys_res = sead::DynamicCast<ksys::res::Resource>(mResource)) {
                    if (context)
                        ksys_res->setContext(context);
                    ok = ksys_res->finishParsing(context);
                }
                mStatus = ok ? Status::_14 : Status::_15;
                if (ok) {
                    adjustHeapAndArena();
                    mEvent.setSignal();
                    return true;
                }
            }
            adjust_heap_and_dec_ref();
            set_status_12 = false;
        }
    }

    if (set_status_12)
        mStatus = Status::_12;

    mEvent.setSignal();

    ksys::res::stubbedLogFunction();
    return false;
}

bool ResourceUnit::waitForTask1() {
    mTask1.wait();
    return true;
}

void ResourceUnit::adjustHeapAndArena() {
    if (mStatusFlags.isOn(StatusFlag::HasHeap)) {
        mStatusFlags.set(StatusFlag::_8);
        return;
    }

    if (mStatusFlags.isOn(StatusFlag::_8)) {
        auto* arena = mArena1;

        if (mStatusFlags.isOff(StatusFlag::_2)) {
            arena->addSize(mHeap ? mHeap->getSize() : 0);
            mStatusFlags.set(StatusFlag::_2);
        }

        if (mStatusFlags.isOff(StatusFlag::_4) &&
            mStatusFlags.isOff(StatusFlag::NeedToIncrementRefCount)) {
            arena->addSize2(mHeap ? mHeap->getSize() : 0);
            mStatusFlags.set(StatusFlag::_4);
            return;
        }

    } else {
        if (mStatusFlags.isOn(StatusFlag::_40000)) {
            ControlTaskRequest req{false};
            req.mHasHandle = false;
            req.mSynchronous = false;
            req.mLaneId = u8(res::ResourceMgrTask::LaneId::_10);
            req.mThread = res::ResourceMgrTask::instance()->getResourceMemoryThread();
            req.mDelegate = &res::ResourceMgrTask::instance()->getUnitAdjustHeapFn();
            req.mUserData = this;
            req.mName = "HeapAdjust";
            mTask2.submitRequest(req);
            return;
        }

        auto* arena = mArena1;

        if (mStatusFlags.isOff(StatusFlag::_2)) {
            arena->addSize(mHeap ? mHeap->getSize() : 0);
            mStatusFlags.set(StatusFlag::_2);
        }

        if (mStatusFlags.isOff(StatusFlag::_4) &&
            mStatusFlags.isOff(StatusFlag::NeedToIncrementRefCount)) {
            arena->addSize2(mHeap ? mHeap->getSize() : 0);
            mStatusFlags.set(StatusFlag::_4);
            return;
        }
    }
}

bool ResourceUnit::waitForTask1(const sead::TickSpan& span) {
    return mTask1.wait(span);
}

void ResourceUnit::detachFromHandle_(Handle* handle) {
    handle->setUnit(nullptr);
}

void ResourceUnit::setStatusFlag10000() {
    mStatusFlags.set(StatusFlag::_10000);
}

bool ResourceUnit::isStatusFlag10000Set() const {
    return mStatusFlags.isOn(StatusFlag::_10000);
}

}  // namespace ksys::res
