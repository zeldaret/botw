#include "KingSystem/ActorSystem/actBaseProcDeleter.h"
#include "KingSystem/ActorSystem/actActorParamMgr.h"
#include "KingSystem/ActorSystem/actBaseProc.h"
#include "KingSystem/Utils/SafeDelete.h"
#include "KingSystem/Utils/Thread/ManagedTask.h"
#include "KingSystem/Utils/Thread/TaskMgr.h"
#include "KingSystem/Utils/Thread/TaskQueue.h"

namespace ksys::act {

BaseProcDeleter::BaseProcDeleter() = default;

bool BaseProcDeleter::doPreDelete(void* proc) {
    BaseProc::PreDeleteArg arg;
    static_cast<BaseProc*>(proc)->doPreDelete(arg);
    return true;
}

bool BaseProcDeleter::doUnloadParam(void* actor_param) {
    ActorParamMgr::instance()->unloadParam(static_cast<ActorParam*>(actor_param));
    return true;
}

BaseProcDeleter::~BaseProcDeleter() {
    if (mTaskMgr) {
        mTaskMgr->finalize();
        util::safeDelete(mTaskMgr);
    }
}

void BaseProcDeleter::init(const InitArg& arg) {
    auto* heap = arg.heap;
    mTaskQueue = arg.task_queue;
    mTaskMgr = new (heap) util::TaskMgr(heap);
    mTaskMgr->init<util::ManagedTask>(arg.task_queue_size, heap);
}

bool BaseProcDeleter::requestPreDelete(BaseProc* proc) {
    util::TaskRequest request{false};
    request.mSynchronous = false;
    request.mQueue = mTaskQueue;
    request.mDelegate = &mPreDeleteDelegate;
    request.mUserData = proc;
    request.mLaneId = u8(TaskLane::PreDelete);
    request.mName = "PreDelete";

    util::TaskMgrRequest req;
    req.request = &request;
    return mTaskMgr->trySubmitRequest(req);
}

void BaseProcDeleter::requestUnloadActorParam(ActorParam* param) {
    util::TaskRequest request{false};
    request.mSynchronous = false;
    request.mQueue = mTaskQueue;
    request.mDelegate = &mUnloadActorParamDelegate;
    request.mUserData = param;
    request.mLaneId = u8(TaskLane::UnloadActorParam);
    request.mName = "UnloadActorParam";

    util::TaskMgrRequest req;
    req.request = &request;
    mTaskMgr->submitRequest(req);
}

void BaseProcDeleter::unblockTasks() {
    mTaskQueue->unblockTasks(u8(TaskLane::PreDelete));
    mTaskQueue->unblockTasks(u8(TaskLane::UnloadActorParam));
}

}  // namespace ksys::act
