#include "KingSystem/Physics/System/physRayCastRequestMgr.h"
#include <cmath>
#include <prim/seadScopedLock.h>
#include "KingSystem/Framework/frmWorkerSupportThreadMgr.h"
#include "KingSystem/Physics/System/physRayCastForRequest.h"
#include "KingSystem/ksys.h"

namespace ksys::phys {

RayCastRequestMgr::RayCastRequestMgr() = default;

RayCastRequestMgr::~RayCastRequestMgr() = default;

void RayCastRequestMgr::init(sead::Heap* heap, int pool_size) {
    mLargestRecordedQueueSize = 0;
    for (auto it = mQueuedList.robustBegin(); it != mQueuedList.robustEnd(); it++)
        mQueuedList.erase(&*it);

    for (int i = 0; i < pool_size; ++i) {
        auto* ray_cast = new (heap, 0x10) RayCastForRequest(this);
        mFreeList.pushBack(&ray_cast->mListNode);
    }

    mWorkerFunction.bind(this, &RayCastRequestMgr::processRequests);
}

bool RayCastRequestMgr::processRequests(void*) {
    for (int i = 0; i < mBatchSize; ++i) {
        mCS.lock();
        auto* request = mQueuedList.popFront();
        if (!request) {
            mCS.unlock();
            return true;
        }
        request->mList = nullptr;
        mCS.unlock();

        request->mData->worldRayCast(request->mData->mRequestContactLayerType);
    }

    return true;
}

void RayCastRequestMgr::clearRequests() {
    {
        auto lock = sead::makeScopedLock(mCS);
        while (!mQueuedList.isEmpty()) {
            auto* request = mQueuedList.popFront();
            if (!request)
                continue;

            auto* ray_cast = request->mData;
            request->mList = nullptr;
            releaseRequest(*ray_cast);
        }
    }
    mLargestRecordedQueueSize = 0;
}

void RayCastRequestMgr::releaseRequest(RayCastForRequest& ray_cast) {
    auto lock = sead::makeScopedLock(mCS);
    ray_cast.mRigidBodyHitCallback = nullptr;
    mFreeList.pushBack(&ray_cast.mListNode);
}

RayCastForRequest* RayCastRequestMgr::allocRequest(SystemGroupHandler* group_handler,
                                                   GroundHit ground_hit) {
    auto lock = sead::makeScopedLock(mCS);

    auto* request = mFreeList.popFront();
    if (!request)
        return nullptr;

    request->mList = nullptr;

    if (request->mData->_98) {
        mFreeList.pushBack(request);
        return nullptr;
    }

    request->mData->reset();
    request->mData->mGroupHandler = group_handler;
    request->mData->setGroundHit(ground_hit);
    request->mData->mNormalCheckingMode = RayCast::NormalCheckingMode::_0;
    return request->mData;
}

static bool isVectorInvalid(const sead::Vector3f& vec) {
    for (int i = 0; i < 3; ++i) {
        if (std::isnan(vec.e[i]))
            return true;
    }
    return false;
}

bool RayCastRequestMgr::submitRequest(RayCastForRequest& ray_cast, ContactLayerType layer_type) {
    if (isVectorInvalid(ray_cast.mFrom) || isVectorInvalid(ray_cast.mTo))
        return false;

    if (ray_cast.mListNode.isLinked())
        return false;

    auto lock = sead::makeScopedLock(mCS);

    ray_cast.mRequestContactLayerType = layer_type;
    mQueuedList.pushBack(&ray_cast.mListNode);

    if (mQueuedList.size() > mLargestRecordedQueueSize)
        mLargestRecordedQueueSize = mQueuedList.size();

    return true;
}

bool RayCastRequestMgr::isRequestQueued(const RayCastForRequest& ray_cast) const {
    return ray_cast.mListNode.mList == &mQueuedList;
}

bool RayCastRequestMgr::isRequestFinished(const RayCastForRequest& ray_cast) const {
    return ray_cast.mListNode.mList == &mFreeList;
}

void RayCastRequestMgr::scheduleRequestProcessing() {
    if (!isGameOver())
        frm::WorkerSupportThreadMgr::instance()->submitRequest(5, &mWorkerFunction);
}

}  // namespace ksys::phys
