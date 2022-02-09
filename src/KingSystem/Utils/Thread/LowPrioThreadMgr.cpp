#include "KingSystem/Utils/Thread/LowPrioThreadMgr.h"
#include <limits>
#include <mc/seadCoreInfo.h>
#include <thread/seadThreadUtil.h>
#include "KingSystem/Utils/SafeDelete.h"
#include "KingSystem/Utils/Thread/TaskQueue.h"

namespace ksys::util {

SEAD_SINGLETON_DISPOSER_IMPL(LowPrioThreadMgr)

LowPrioThreadMgr::~LowPrioThreadMgr() {
    const s32 num_tasks = mCoreThreadTasks.size();

    for (s32 i = 0; i < num_tasks; i++) {
        mCoreThreadTasks[i].task_thread->quitAndWaitDoneSingleThread(false);
        util::safeDelete(mCoreThreadTasks[i].task_thread);
        util::safeDelete(mCoreThreadTasks[i].task_mgr);
    }
    mCoreThreadTasks.freeBuffer();
}

bool LowPrioThreadMgr::startThread(const LowPrioThreadMgr::InitArg& initArg) {
    const u32 num_cores = sead::CoreInfo::getNumCores();

    mCoreThreadTasks.tryAllocBuffer(num_cores, initArg.heap);

    for (u32 i = 0; i < num_cores; i++) {
        auto* task_mgr = new (initArg.heap) TaskMgr(initArg.heap);
        task_mgr->init<ManagedTask>(initArg.queue_size, initArg.heap);
        mCoreThreadTasks[i].task_mgr = task_mgr;

        sead::SafeString name;
        auto* new_thread = new (initArg.heap) TaskThread(
            name, initArg.heap, sead::ThreadUtil::ConvertPrioritySeadToPlatform(initArg.priority),
            sead::MessageQueue::BlockType::Blocking, std::numeric_limits<s32>::max(), 0x100000, 32);

        {
            TaskThread::InitArg arg;

            arg.queue = nullptr;
            arg.heap = initArg.heap;
            arg.num_lanes = 3;
            arg.batch_size = 1;

            new_thread->init(arg);
        }

        mCoreThreadTasks[i].task_thread = new_thread;

        new_thread->setAffinity(sead::CoreIdMask(i));
        new_thread->start();
    }

    return true;
}

bool LowPrioThreadMgr::submitRequest(const LowPrioThreadMgr::Request& request) {
    const s32 num_tasks = mCoreThreadTasks.size();
    const sead::BitFlag32 mask = request.flags;
    s32 thread_idx = -1;
    s32 min = std::numeric_limits<s32>::max();

    for (s32 i = 0; i < num_tasks; i++) {
        if (mask.isOnBit(i) && mCoreThreadTasks[i].task_thread) {
            s32 active_tasks = mCoreThreadTasks[i].task_thread->getNumActiveTasks();

            if (active_tasks < min) {
                thread_idx = i;
                min = active_tasks;
            }
        }
    }

    TaskRequest taskRequest(false);
    taskRequest.mPostRunCallback = request.post_callback;
    taskRequest.mRemoveCallback = request.remove_callback;
    taskRequest.mName = request.name;
    taskRequest.mUserData = request.user_data;
    taskRequest.mDelegate = request.delegate;
    taskRequest.mHasHandle = true;
    taskRequest.mSynchronous = false;
    taskRequest.mLaneId = request.lane_id;
    taskRequest.mThread = mCoreThreadTasks[thread_idx].task_thread;

    TaskMgrRequest mgrRequest;
    mgrRequest.handle = request.handle;
    mgrRequest.request = &taskRequest;
    mgrRequest.task = request.task;

    TaskMgr* task_mgr = request.mgr ? request.mgr : mCoreThreadTasks[thread_idx].task_mgr;

    if (request.try_submit) {
        return task_mgr->trySubmitRequest(mgrRequest);
    }

    task_mgr->submitRequest(mgrRequest);
    return true;
}

void LowPrioThreadMgr::pauseAllTasks() {
    const s32 num_tasks = mCoreThreadTasks.size();

    for (s32 i = 0; i < num_tasks; i++) {
        mCoreThreadTasks[i].task_thread->pauseAndWaitForAck();
    }
}

void LowPrioThreadMgr::resumeAllTasks() {
    const s32 num_tasks = mCoreThreadTasks.size();

    for (s32 i = 0; i < num_tasks; i++) {
        mCoreThreadTasks[i].task_thread->resume();
    }
}

void LowPrioThreadMgr::sub_710127AC40() {}

}  // namespace ksys::util
