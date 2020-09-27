#include "KingSystem/Resource/resUnit.h"
#include <filedevice/seadArchiveFileDevice.h>
#include <resource/seadArchiveRes.h>
#include "KingSystem/Resource/resCache.h"
#include "KingSystem/Resource/resEntryFactory.h"
#include "KingSystem/Resource/resLoadRequest.h"
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
        request._c = 2;
        request.mPack = arg.load_req->mPackHandle;
        mArchiveRes = sead::DynamicCast<sead::ArchiveRes>(mArchiveResHandle.load("", request));
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
        mArchiveResHandle.unload();
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

// NON_MATCHING: ldr + sxtw -> ldrsw
void ResourceUnit::updateStatus() {
    static const Status sMap[] = {Status::_8, Status::_11, Status::_11, Status::_14, Status::_14};
    if (Status::_2 <= mStatus && mStatus <= Status::_6)
        mStatus = sMap[s32(mStatus)];
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

bool ResourceUnit::isStatus9_12_15() const {
    return mStatus == Status::_9 || mStatus == Status::_12 || mStatus == Status::_15;
}

// NON_MATCHING: branching for the second if
bool ResourceUnit::isParseOk() const {
    auto* ksys_res = sead::DynamicCast<res::Resource>(mResource);

    if (mStatus == Status::_14)
        return true;

    if (mStatus == Status::_8 && !ksys_res)
        return mResource != nullptr;

    if (mStatus == Status::_8 && ksys_res)
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

}  // namespace ksys::res
