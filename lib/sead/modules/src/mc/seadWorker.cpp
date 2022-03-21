#include "mc/seadWorker.h"
#include "prim/seadScopedLock.h"

namespace sead
{
Worker::Worker(WorkerMgr* mgr, u32 num_jobs, s32 stack_size, s32 priority, const SafeString& name)
    : Thread(name, nullptr, priority, MessageQueue::BlockType::Blocking, 0x7FFFFFFF, stack_size, 1),
      mMgr(mgr)
{
    mJobQueues.allocBufferAssert(num_jobs, nullptr);
    mEvent.setSignal();
}

bool Worker::pushJobQueue(const char* description, JobQueue* queue, JobQueuePushType type)
{
    ScopedLock<JobQueueLock> lock(&mLock);

    bool ret;
    if (type == JobQueuePushType::cForward)
        ret = mJobQueues.pushBack(queue);
    else
        ret = mJobQueues.pushBackwards(queue);

    queue->setDescription(description);
    return ret;
}

void Worker::clearJobQQ()
{
    ScopedLock<JobQueueLock> lock(&mLock);
    mJobQueues.clear();
}

void Worker::calc_(MessageQueue::Element msg)
{
    if (msg == cMsg_Process)
        proc_();
}

void Worker::proc_()
{
    ++mNumRuns;
    mLastRun.setNow();
    mWorkerState = Worker::State::cRunning;

    JobQueue* queue = getNextJQ_();
    const u32 core = mCore;
    while (queue)
    {
        mCurrentQueue = queue;
        mCurrentQueueDescription = queue->getDescription();

        const auto granularity = queue->getGranularity(core);

        // Process the queue.
        queue->resetFinishEvent();
        volatile bool ok = false;
        u32 total_finished_jobs = 0;
        while (!ok)
        {
            u32 finished_jobs = 0;
            ok = queue->run(granularity, &finished_jobs, this);
            total_finished_jobs += finished_jobs;
        }

        const u32 num_done = queue->addNumDoneJobs(total_finished_jobs);

        if (num_done >= queue->getNumJobs())
            queue->signalFinishEvent();

        mWorkerState = Worker::State::cFinished;
        queue->FINISH(mCore);
        mWorkerState = Worker::State::cWaitingAtWorker;

        mWorkerState = Worker::State::cRunning;
        queue = getNextJQ_();
    }

    mCurrentQueue = nullptr;
    mCurrentQueueDescription = nullptr;
    mWorkerState = Worker::State::cSleep;
    mEvent.setSignal();
}

JobQueue* Worker::getNextJQ_()
{
    ScopedLock<JobQueueLock> lock(&mLock);
    return mJobQueues ? mJobQueues.popFront() : nullptr;
}

void Worker::wakeup_(MessageQueue::Element msg)
{
    SEAD_ASSERT_MSG(mWorkerState.load() == Worker::State::cSleep, "invalid state[%s]",
                    mWorkerState.load().text());

    if (mJobQueues)
    {
        mEvent.resetSignal();
        mWorkerState = Worker::State::cWakeup;
        const bool success = sendMessage(msg, MessageQueue::BlockType::NonBlocking);
        SEAD_ASSERT(success);
    }
}
}  // namespace sead
