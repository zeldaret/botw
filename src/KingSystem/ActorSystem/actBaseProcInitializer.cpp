#include "KingSystem/ActorSystem/actBaseProcInitializer.h"
#include <heap/seadExpHeap.h>
#include <thread/seadThreadUtil.h>
#include "KingSystem/ActorSystem/actBaseProcCreateTask.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Resource/resGameResourceSystem.h"
#include "KingSystem/Utils/Debug.h"
#include "KingSystem/Utils/SafeDelete.h"
#include "KingSystem/Utils/Thread/GameTaskThread.h"
#include "KingSystem/Utils/Thread/TaskMgr.h"
#include "KingSystem/Utils/Thread/TaskQueue.h"
#include "KingSystem/Utils/Thread/TaskQueueLock.h"
#include "KingSystem/Utils/Thread/TaskThread.h"

namespace ksys::act {

BaseProcInitializer::BaseProcInitializer() = default;

BaseProcInitializer::~BaseProcInitializer() {
    mTaskMgr->finalize();
    mTaskMgr = nullptr;

    for (int i = 0; i < mThreads.size(); ++i) {
        mThreads[i].thread->quitAndWaitDoneSingleThread(false);
        if (mThreads[i].thread)
            delete mThreads[i].thread;
        mThreads[i].thread = nullptr;
    }

    mThreads.freeBuffer();
    util::safeDelete(mTaskQueue);
}

void BaseProcInitializer::init(sead::Heap* parent_heap, const BaseProcInitializerArgs& args) {
    constexpr int NumThreads = 3;

    mHeap = sead::ExpHeap::create(0, "BaseProcInitializer", parent_heap, sizeof(void*),
                                  sead::Heap::cHeapDirection_Forward, false);

    mThreads.allocBufferAssert(NumThreads, mHeap);

    const auto init_queue = [&] {
        mTaskQueue = new (mHeap) util::TaskQueue(mHeap);
        util::TaskQueue::InitArg arg;
        arg.enable_locks = true;
        arg.heap = mHeap;
        arg.num_lanes = 5;
        arg.max_num_threads = NumThreads;
        arg.task_selection_delegate = args.task_selector;
        mTaskQueue->init(arg);
    };
    init_queue();

    mTaskMgr = new (mHeap) util::TaskMgr(mHeap);
    mTaskMgr->initAndCheckType<BaseProcCreateTask>(args.queue_size, mHeap);

    for (int i = 0; i < NumThreads; ++i) {
        mThreads[i].thread_name.format("%s", args.thread_name.cstr());
        mThreads[i].thread = new (mHeap) util::GameTaskThread(
            mThreads[i].thread_name, mHeap, sead::ThreadUtil::ConvertPrioritySeadToPlatform(20),
            sead::MessageQueue::BlockType::Blocking, 0x7FFFFFFF, 0x100000, 64);
        {
            util::TaskThread::InitArg arg;
            arg.num_lanes = 5;
            arg.heap = mHeap;
            arg.queue = mTaskQueue;
            arg.batch_size = 1;
            mThreads[i].thread->init(arg);
        }
        mThreads[i].thread->setAffinity(sead::CoreIdMask(i));
        mThreads[i].thread->start();
        mThreads[i].valid = true;
    }

    mHeap->adjust();
    mThreads[0].thread->quitAndWaitDoneSingleThread(false);
    util::safeDelete(mThreads[0].thread);
}

void BaseProcInitializer::deleteThreadIfPaused() {
    if (mThreads[0].thread && mThreads[0].thread->isPaused()) {
        mThreads[0].thread->quitAndWaitDoneSingleThread(false);
        util::safeDelete(mThreads[0].thread);
    }
}

bool BaseProcInitializer::requestCreateBaseProc(const BaseProcCreateRequest& req) {
    if (!mActorGenerationEnabled) {
        if (req.task_data->mProcHandle)
            req.task_data->mProcHandle->setFailed(true);
        return false;
    }

    auto* data = req.task_data;
    // XXX: was this meant to log the BaseProc class and its name, rather than print the name twice?
    util::PrintDebugFmt("BaseProcInitializer::requestCreateBaseProc: actor %s (%s)",
                        data->mProcName.cstr(), data->mProcName.cstr());

    BaseProcCreateTaskRequest task_req;
    task_req.mHasHandle = req.task_data->mProcHandle != nullptr;
    task_req.mSynchronous = false;
    task_req.mLaneId = req.task_lane_id;
    task_req.mQueue = mTaskQueue;
    task_req.mUserData = nullptr;
    task_req.mRemoveCallback = req.task_remove_callback;
    task_req.mData = req.task_data;
    if (req.task_data)
        task_req.mName = req.task_data->mProcName;

    util::TaskMgrRequest mgr_req;
    if (req.task_data->mProcHandle) {
        if (!req.task_data->mProcHandle->allocUnit()) {
            req.task_data->mProcHandle->setFailed(true);
            return false;
        }

        mgr_req.task = req.task_data->mProcHandle->getCreateTask();
        if (!mgr_req.task) {
            req.task_data->mProcHandle->setFailed(true);
            return false;
        }
    } else {
        mgr_req.task = nullptr;
    }

    mgr_req.request = &task_req;
    mTaskMgr->submitRequest(mgr_req);
    return true;
}

BaseProc* BaseProcInitializer::createBaseProc(const BaseProcCreateRequest& req) {
    res::GameResourceSystem::instance()->pauseCompaction();

    BaseProcCreateArg arg;
    arg.heap = req.task_data->mHeap;
    arg.heap2 = req.task_data->mHeap;
    arg.proc_class = req.task_data->mProcClass;
    arg.proc_name = req.task_data->mProcName;
    arg.mubin_iter = req.task_data->mMubinIter;
    arg.map_object = req.task_data->mMapObject;
    arg.params = req.task_data->mParams;
    if (auto* other = req.task_data->mOtherProc)
        arg.proc_link.acquire(other, false);
    else
        arg.proc_link.reset();

    BaseProc* result = nullptr;
    BaseProc* proc = req.task_data->mCreateDelegate->invoke(arg);

    if (proc && !proc->isDeletedOrDeleting()) {
        if (proc->init(arg.heap2, req.task_data->mSleepAfterInit))
            result = proc;
    } else if (arg.map_object) {
        arg.map_object->onBaseProcCreated(proc);
    }

    if (proc)
        proc->setInitializedFlag();

    res::GameResourceSystem::instance()->resumeCompaction();
    return result;
}

void BaseProcInitializer::restartThreads() {
    for (int i = 0; i < mThreads.size(); ++i) {
        if (!mThreads[i].thread)
            continue;

        if (i == 0 && mThreads[0].valid) {
            mThreads[0].thread->pauseAndWaitForAck();
            mThreads[0].thread->resume();
        } else if (i != 0) {
            mThreads[i].thread->pauseAndWaitForAck();
            mThreads[i].thread->resume();
        }
    }
}

void BaseProcInitializer::blockPendingTasks() {
    mTaskQueue->blockTasks(u8(BaseProcCreateTask::LaneId::_0));
    mTaskQueue->blockTasks(u8(BaseProcCreateTask::LaneId::_1));
    mTaskQueue->blockTasks(u8(BaseProcCreateTask::LaneId::_2));
}

void BaseProcInitializer::pauseThreads() {
    for (int i = 0; i < mThreads.size(); ++i) {
        if (mThreads[i].thread)
            mThreads[i].thread->pauseAndWaitForAck();
    }
}

void BaseProcInitializer::resumeThreads() {
    for (int i = 0; i < mThreads.size(); ++i) {
        if (mThreads[i].thread)
            mThreads[i].thread->resume();
    }
}

void BaseProcInitializer::unblockPendingTasks() {
    mTaskQueue->unblockTasks(u8(BaseProcCreateTask::LaneId::_2));
    mTaskQueue->unblockTasks(u8(BaseProcCreateTask::LaneId::_1));
    mTaskQueue->unblockTasks(u8(BaseProcCreateTask::LaneId::_0));
}

void BaseProcInitializer::pauseMainThread() {
    if (mThreads[0].thread) {
        mThreads[0].thread->pause();
        mThreads[0].valid = false;
    }
}

void BaseProcInitializer::resumeMainThread() {
    mThreads[0].valid = true;
    if (!mThreads[0].thread) {
        mThreads[0].thread = new (mHeap) util::GameTaskThread(
            mThreads[0].thread_name, mHeap, sead::ThreadUtil::ConvertPrioritySeadToPlatform(20),
            sead::MessageQueue::BlockType::Blocking, 0x7FFFFFFF, 0x100000, 64);
        {
            util::TaskThread::InitArg arg;
            arg.num_lanes = 5;
            arg.heap = mHeap;
            arg.queue = mTaskQueue;
            arg.batch_size = 1;
            mThreads[0].thread->init(arg);
        }
        mThreads[0].thread->setAffinity(sead::CoreIdMask(sead::CoreId::cMain));
        mThreads[0].thread->start();
    }
    mThreads[0].thread->resume();
}

bool BaseProcInitializer::isAnyThreadActive() const {
    for (int i = 0; i < mThreads.size(); ++i) {
        if (mThreads[i].thread && mThreads[i].thread->isActiveAndReceivedQueueUpdateMsg())
            return true;
    }
    return false;
}

void BaseProcInitializer::waitForTaskQueuesToEmpty() {
    mTaskQueue->waitForLaneToEmpty(u8(BaseProcCreateTask::LaneId::_2));
    mTaskQueue->waitForLaneToEmpty(u8(BaseProcCreateTask::LaneId::_1));
    mTaskQueue->waitForLaneToEmpty(u8(BaseProcCreateTask::LaneId::_0));
}

void BaseProcInitializer::cancelTasks() {
    int n = 0;
    n += mThreads[1].thread->getTaskQueue()->countTasksInLane(u8(BaseProcCreateTask::LaneId::_0));
    n += mThreads[1].thread->getTaskQueue()->countTasksInLane(u8(BaseProcCreateTask::LaneId::_1));
    n += mThreads[1].thread->getTaskQueue()->countTasksInLane(u8(BaseProcCreateTask::LaneId::_2));
    util::PrintDebugFmt("Cancelling %d tasks", n);

    for (int i = 0; i < mThreads.size(); ++i) {
        if (!mThreads[i].thread)
            continue;
        mThreads[i].thread->cancelTasks(u8(BaseProcCreateTask::LaneId::_0));
        mThreads[i].thread->cancelTasks(u8(BaseProcCreateTask::LaneId::_1));
        mThreads[i].thread->cancelTasks(u8(BaseProcCreateTask::LaneId::_2));
    }
}

int BaseProcInitializer::getQueueSize(int x) const {
    if (x != -1)
        return -1;

    int count = 0;
    count += mTaskQueue->countTasksInLane(u8(BaseProcCreateTask::LaneId::_2));
    count += mTaskQueue->countTasksInLane(u8(BaseProcCreateTask::LaneId::_1));
    count += mTaskQueue->countTasksInLane(u8(BaseProcCreateTask::LaneId::_0));
    return count;
}

void BaseProcInitializer::removeTasksIf(sead::IDelegate1R<util::Task*, bool>& predicate) {
    util::TaskQueueLock lock;
    auto it = mTaskQueue->activeTasksRobustBegin(&lock);
    const auto end = mTaskQueue->activeTasksRobustEnd();
    for (; it != end; ++it) {
        if (predicate(std::addressof(*it)))
            it->removeFromQueue();
    }
}

void BaseProcInitializer::setActorGenerationEnabled(bool enabled) {
    mActorGenerationEnabled = enabled;
}

}  // namespace ksys::act
