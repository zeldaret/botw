#include "KingSystem/Utils/Thread/LowPrioThreadMgr.h"
#include <limits>
#include <mc/seadCoreInfo.h>
#include <thread/seadThreadUtil.h>
#include "KingSystem/Utils/Thread/TaskQueue.h"

namespace ksys::util {

SEAD_SINGLETON_DISPOSER_IMPL(LowPrioThreadMgr)

auto LowPrioThreadMgr::startThread(LowPrioThreadMgr::InitArg* initArg) -> bool {
    const u32 numCores = sead::CoreInfo::getNumCores();

    mCoreThreadTasks.tryAllocBuffer(numCores, initArg->heap);

    for (u32 i = 0; i < numCores; i++) {
        TaskMgr* taskMgr = new (initArg->heap) TaskMgr(initArg->heap);
        taskMgr->init<ManagedTask>(initArg->queueSize, initArg->heap);
        mCoreThreadTasks[i].taskMgr = taskMgr;

        sead::SafeString name;
        TaskThread* newThread = new (initArg->heap) TaskThread(
            name, initArg->heap, sead::ThreadUtil::ConvertPrioritySeadToPlatform(initArg->priority),
            sead::MessageQueue::BlockType::Blocking, std::numeric_limits<s32>::max(), 0x100000, 32);

        {
            TaskThread::InitArg arg;
            arg.queue = nullptr;
            arg.heap = initArg->heap;
            arg.num_lanes = 3;
            arg.batch_size = 1;

            newThread->init(arg);
        }

        mCoreThreadTasks[i].taskThread = newThread;

        newThread->setAffinity(sead::CoreIdMask(i));
        newThread->start();
    }

    return true;
}

auto LowPrioThreadMgr::submitRequest(const LowPrioThreadMgr::Request& request) -> bool {
    const s32 numCores = mCoreThreadTasks.size();
    const auto mask = request.flags;
    s32 foundIdx = -1;
    s32 min = std::numeric_limits<s32>::max();

    for (s32 i = 0; i < numCores; i++) {
        if (mask.isOnBit(i) && mCoreThreadTasks[i].taskThread) {
            s32 activeTasks = mCoreThreadTasks[i].taskThread->getNumActiveTasks();

            if (activeTasks < min) {
                foundIdx = i;
                min = activeTasks;
            }
        }
    }

    TaskRequest taskRequest(false);
    taskRequest.mPostRunCallback = request.postCallback;
    taskRequest.mRemoveCallback = request.removeCallback;
    taskRequest.mName = request.name;
    taskRequest.mUserData = request.userData;
    taskRequest.mDelegate = request.delegate;
    taskRequest.mHasHandle = true;
    taskRequest.mSynchronous = false;
    taskRequest.mLaneId = request.laneId;
    taskRequest.mThread = mCoreThreadTasks[foundIdx].taskThread;

    TaskMgrRequest mgrRequest;
    mgrRequest.handle = request.handle;
    mgrRequest.request = &taskRequest;
    mgrRequest.task = request.task;

    TaskMgr* taskMgr = request.mgr ? request.mgr : mCoreThreadTasks[foundIdx].taskMgr;

    if (request.unk_00) {
        return taskMgr->trySubmitRequest(mgrRequest);
    }

    taskMgr->submitRequest(mgrRequest);
    return true;
}

auto LowPrioThreadMgr::pauseAllThreads() -> void {
    const s32 numCores = mCoreThreadTasks.size();

    for (s32 i = 0; i < numCores; i++) {
        mCoreThreadTasks[i].taskThread->pauseAndWaitForAck();
    }
}

auto LowPrioThreadMgr::resumeAllThreads() -> void {
    const s32 numCores = mCoreThreadTasks.size();

    for (s32 i = 0; i < numCores; i++) {
        mCoreThreadTasks[i].taskThread->resume();
    }
}

}  // namespace ksys::util
