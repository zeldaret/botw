#include "KingSystem/Framework/frmWorkerSupportThreadMgr.h"
#include <mc/seadCoreInfo.h>
#include <thread/seadDelegateThread.h>
#include <thread/seadThreadUtil.h>
#include "KingSystem/Utils/SafeDelete.h"
#include "KingSystem/Utils/Thread/GameTaskThread.h"
#include "KingSystem/Utils/Thread/ManagedTask.h"
#include "KingSystem/Utils/Thread/ManagedTaskHandle.h"
#include "KingSystem/Utils/Thread/TaskMgr.h"

namespace ksys::frm {

SEAD_SINGLETON_DISPOSER_IMPL(WorkerSupportThreadMgr)

void WorkerSupportThreadMgr::init(sead::Heap* heap) {
    auto* worker = mWorkers;
    for (size_t i = 0; i < NumWorkers; ++i) {
        auto* mgr = new (heap) util::TaskMgr(heap);
        mgr->init<util::ManagedTask>(NumTasks, heap);
        worker->task_mgr = mgr;

        worker->task_handle = new (heap) util::ManagedTaskHandle;
        for (int j = 0; j < NumTasks; ++j)
            worker->tasks[j] = new (heap) util::ManagedTask(heap);

        const auto affinity = [&] {
            if (i == 0)
                return sead::CoreIdMask(sead::CoreId::cSub1);
            return sead::CoreIdMask(sead::CoreId::cSub2);
        }();

        worker->thread_name.format("WorkerSupport[%d]", int(i));
        worker->task_thread = new (heap) util::GameTaskThread(
            worker->thread_name, heap, sead::ThreadUtil::ConvertPrioritySeadToPlatform(17),
            sead::MessageQueue::BlockType::Blocking, 0x7fffffff, 0x20000, 32);

        util::TaskThread::InitArg arg;
        arg.batch_size = 0;
        arg.heap = nullptr;
        arg.queue = nullptr;
        arg.heap = heap;
        arg.num_lanes = 1;
        worker->task_thread->init(arg);
        worker->task_thread->setAffinity(affinity);
        worker->task_thread->start();
        ++worker;
    }

    mSleeperHeap = sead::ExpHeap::create(0x8000, "SleeperHeap", heap, sizeof(void*),
                                         sead::Heap::cHeapDirection_Forward, false);
    initSleeperThreads();
    mSleeperHeap->adjust();
}

void WorkerSupportThreadMgr::initSleeperThreads() {
    for (int i = 0; i < NumWorkers; ++i) {
        const sead::CoreIdMask affinity{sead::CoreId::cSub1 + i};
        if (affinity == sead::CoreIdMask(sead::CoreId::cSub2)) {
            mWorkers[i].thread = new (mSleeperHeap) sead::DelegateThread(
                "Sleeper",
                new (mSleeperHeap) sead::Delegate2<WorkerSupportThreadMgr, sead::Thread*,
                                                   sead::MessageQueue::Element>(
                    this, &WorkerSupportThreadMgr::sleeperThreadFun),
                mSleeperHeap, sead::ThreadUtil::ConvertPrioritySeadToPlatform(15),
                sead::MessageQueue::BlockType::NonBlocking, 0x7fffffff, 0x1000, 32);
            mWorkers[i].thread->setAffinity(affinity);
            mWorkers[i].thread->start();
            mWorkers[i].thread->sendMessage(1, sead::MessageQueue::BlockType::NonBlocking);
        } else {
            mWorkers[i].thread = nullptr;
        }
    }
}

void WorkerSupportThreadMgr::sleeperThreadFun(sead::Thread* thread, sead::MessageQueue::Element) {
    sead::Thread::sleep(sead::TickSpan::fromMicroSeconds(250));
}

static int getWorkerIdx(u32 id) {
    return (id == 1 || id == 4 || id == 6 || id == 3 || id == 7) ? 1 : 0;
}

static int getTaskIdx(u32 id) {
    static constexpr u8 idx[] = {0, 0, 1, 1, 2, 2, 3, 4};
    return idx[id];
}

util::ManagedTask* WorkerSupportThreadMgr::getTask(int id) {
    return mWorkers[getWorkerIdx(id)].tasks[getTaskIdx(id)];
}

void WorkerSupportThreadMgr::submitRequest(int id, util::TaskDelegate* delegate) {
    auto& worker = mWorkers[getWorkerIdx(id)];
    if (mThreadsPaused)
        return;

    util::TaskRequest req{false};
    req.mName = worker.thread_name;
    req.mDelegate = delegate;
    req.mHasHandle = true;
    req.mSynchronous = false;
    req.mThread = worker.task_thread;

    util::TaskMgrRequest task_mgr_req;
    task_mgr_req.request = &req;
    task_mgr_req.handle = worker.task_handle;
    task_mgr_req.task = worker.tasks[getTaskIdx(id)];
    worker.task_mgr->submitRequest(task_mgr_req);
}

void WorkerSupportThreadMgr::waitForTask(int id) {
    if (!mThreadsPaused)
        getTask(id)->wait();
}

void WorkerSupportThreadMgr::pauseThreads() {
    mThreadsPaused = true;
    for (auto& worker : mWorkers)
        worker.task_thread->pauseAndWaitForAck();
}

void WorkerSupportThreadMgr::resumeThreads() {
    mThreadsPaused = false;
    for (auto& worker : mWorkers)
        worker.task_thread->resume();
}

void WorkerSupportThreadMgr::destroyThreads() {
    for (auto& worker : mWorkers) {
        if (worker.thread) {
            worker.thread->quitAndDestroySingleThread(false);
            util::safeDelete(worker.thread);
        }
    }
    mSleeperHeap->freeAll();
}

}  // namespace ksys::frm
