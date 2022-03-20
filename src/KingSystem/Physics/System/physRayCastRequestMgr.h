#pragma once

#include <container/seadTList.h>
#include <hostio/seadHostIONode.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/Utils/Thread/Task.h"

namespace ksys::phys {

class RayCastForRequest;
class SystemGroupHandler;

class RayCastRequestMgr : public sead::hostio::Node {
public:
    RayCastRequestMgr();
    virtual ~RayCastRequestMgr();

    void init(sead::Heap* heap, int pool_size);

    void clearRequests();
    void releaseRequest(RayCastForRequest& ray_cast);
    RayCastForRequest* allocRequest(SystemGroupHandler* group_handler, GroundHit ground_hit);
    bool submitRequest(RayCastForRequest& ray_cast, ContactLayerType layer_type);
    bool isRequestQueued(const RayCastForRequest& ray_cast) const;
    bool isRequestFinished(const RayCastForRequest& ray_cast) const;

    void scheduleRequestProcessing();

private:
    bool processRequests(void*);

    sead::CriticalSection mCS;
    sead::TList<RayCastForRequest*> mQueuedList;
    sead::TList<RayCastForRequest*> mFreeList;
    util::TaskDelegateT<RayCastRequestMgr> mWorkerFunction;
    /// The number of requests to process per batch.
    int mBatchSize = 1;
    int mLargestRecordedQueueSize = 0;
};

}  // namespace ksys::phys
