#pragma once

#include <array>
#include "container/seadBuffer.h"
#include "framework/seadInfLoopChecker.h"
#include "heap/seadDisposer.h"
#include "hostio/seadHostIONode.h"
#include "mc/seadCoreInfo.h"
#include "mc/seadJobQueue.h"
#include "mc/seadWorker.h"
#include "time/seadTickSpan.h"
#include "time/seadTickTime.h"

namespace sead
{
class WorkerMgr : public hostio::Node
{
public:
    struct InitializeArg
    {
        InitializeArg();

        std::array<s32, 3> thread_priorities;
        std::array<u32, 3> thread_stack_sizes;
        u32 worker_num_jobs;
        const char* name;
    };

    WorkerMgr();
    virtual ~WorkerMgr() = default;
    WorkerMgr(const WorkerMgr&) = delete;
    auto operator=(const WorkerMgr&) = delete;

    virtual void initialize(const InitializeArg& arg);
    void finalize();

    void pushJobQueue(JobQueue* queue, CoreIdMask core_id_mask, SyncType sync_type,
                      JobQueuePushType push_type);
    void pushJobQueue(const char* context_name, JobQueue* queue, CoreIdMask core_id_mask,
                      SyncType sync_type, JobQueuePushType push_type);
    void run();
    void sync();
    bool isAllWorkerSleep() const;

protected:
    void onInfLoop_(const InfLoopChecker::InfLoopParam& param);

    InfLoopChecker::InfLoopEvent::Slot mInfLoopEventSlot;
    Buffer<Worker*> mWorkers;
    Buffer<JobQueue*> mJobQueues;
    u32 mNumJobQueues;
    bool mProcessJobQueues = false;
    u32 mNumWakeups = 0;
    TickTime mLastWakeup;
    TickSpan mWaitDuration = TickSpan::makeFromMilliSeconds(1);
};
}  // namespace sead
