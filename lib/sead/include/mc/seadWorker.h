#pragma once

#include "container/seadRingBuffer.h"
#include "mc/seadJobQueue.h"
#include "prim/seadEnum.h"
#include "prim/seadSafeString.h"
#include "thread/seadEvent.h"
#include "thread/seadThread.h"
#include "time/seadTickTime.h"

namespace sead
{
class WorkerMgr;

SEAD_ENUM(JobQueuePushType, cForward, cBackward)

class Worker : public Thread
{
public:
    static constexpr MessageQueue::Element cMsg_Process = 1;

    SEAD_ENUM(State, cSleep, cWakeup, cRunning, cRunning_WaitLock, cRunning_GetLock, cRunning_Run,
              cRunning_AfterRun, cRunning_BeforeReturn, cRunning_AllJobDoneReturn, cFinished,
              cWaitingAtWorker)

    Worker(WorkerMgr* mgr, u32 num_jobs, s32 stack_size, s32 priority, const SafeString& name);

    bool pushJobQueue(const char* name, JobQueue* queue, JobQueuePushType type);
    void clearJobQQ();

    void setState(Worker::State state) { mWorkerState = state; }

protected:
    friend class WorkerMgr;

    void calc_(MessageQueue::Element msg) override;
    virtual void proc_();

    JobQueue* getNextJQ_();
    void wakeup_(MessageQueue::Element msg);

    CoreId mCore = 0;
    Atomic<Worker::State> mWorkerState{sead::AtomicDirectInitTag{}, Worker::State::cSleep};
    WorkerMgr* mMgr = nullptr;
    RingBuffer<JobQueue*> mJobQueues;
    JobQueueLock mLock;
    JobQueue* mCurrentQueue = nullptr;
    const char* mCurrentQueueDescription = nullptr;
    u32 mNumRuns = 0;
    TickTime mLastRun;
    Event mEvent{true};
};
}  // namespace sead
