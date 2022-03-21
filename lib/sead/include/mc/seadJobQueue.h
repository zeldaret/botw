#pragma once

#include "basis/seadTypes.h"
#include "container/seadBuffer.h"
#include "container/seadSafeArray.h"
#include "framework/seadProcessMeterBar.h"
#include "hostio/seadHostIONode.h"
#include "mc/seadCoreInfo.h"
#include "mc/seadJob.h"
#include "prim/seadEnum.h"
#include "prim/seadNamable.h"
#include "thread/seadAtomic.h"
#include "thread/seadEvent.h"

namespace sead
{
class Heap;
class Worker;

SEAD_ENUM(SyncType, cNoSync, cCore, cThread)

class PerfJobQueue
{
public:
    void initialize(const char* name, Heap* heap);
    void finalize();
    void reset();

    void measureBeginDeque();
    void measureEndDeque();
    void measureBeginRun();
    void measureEndRun();

    const Color4f& getBarColor(u32 idx) const;
    void attachProcessMeter();
    void detachProcessMeter();

private:
    Buffer<MultiProcessMeterBar<512>> mBars;
    Buffer<u32> mInts;
    MultiProcessMeterBar<1> mProcessMeterBar;
};

class JobQueueLock
{
public:
    void lock()
    {
        while (mSpinLock.load() == 1)
            continue;
        while (!mSpinLock.compareExchange(0, 1))
            continue;
    }

    void unlock()
    {
        std::atomic_thread_fence(std::memory_order_seq_cst);
        while (!mSpinLock.compareExchange(1, 0))
            continue;
    }

private:
    Atomic<u32> mSpinLock = 0;
};

class JobQueue : public hostio::Node, public INamable
{
public:
    enum class Status : int
    {
        _0 = 0,
        _1 = 1,
        _3 = 3,
        _5 = 5,
        _6 = 6,
    };

    JobQueue();

    virtual void begin() {}
    virtual bool run(u32 size, u32* finished_jobs, Worker* worker);
    void runAll(u32* finished_jobs);

    virtual u32 getNumJobs() const { return 0; }
    bool isAllParticipantThrough() const;

    u32 getGranularity(u32 core) { return mGranularity[core]; }
    void setGranularity(CoreId core, u32 x);
    void setGranularity(u32);
    void setCoreMaskAndWaitType(CoreIdMask mask, SyncType type);

    void FINISH(CoreId core);
    void wait_AT_WORKER();
    void wait();

    const char* getDescription() const { return mDescription; }
    void setDescription(const char* description) { mDescription = description; }

    void signalFinishEvent() { mFinishEvent.setSignal(); }
    void resetFinishEvent() { mFinishEvent.resetSignal(); }
    u32 addNumDoneJobs(u32 num) { return mNumDoneJobs.fetchAdd(num); }

protected:
    virtual bool isDone_();

    SyncType mSyncType = SyncType::cNoSync;
    JobQueueLock mLock;
    CoreIdMask mMask;
    Event mFinishEvent{true};
    SafeArray<u32, 3> mGranularity;
    SafeArray<u32, 3> mCoreEnabled;
    Atomic<u32> mNumDoneJobs = 0;

    Atomic<Status> mStatus = Status::_0;
    const char* mDescription = "NoName";

#ifdef SEAD_DEBUG
    PerfJobQueue mPerf;
#endif
};

class FixedSizeJQ : public JobQueue
{
public:
    FixedSizeJQ();

#ifdef SEAD_DEBUG
    void listenPropertyEvent(const hostio::PropertyEvent* event) override;
    void genMessage(hostio::Context* context) override;
#endif

    void begin() override;
    bool run(u32 size, u32* finished_jobs, Worker* worker) override;
    u32 getNumJobs() const override;

    void initialize(u32 size, Heap* heap);
    void finalize();

    bool enque(Job* job);
    bool enqueSafe(Job* job);
    Job* deque();
    u32 deque(Job** jobs, u32 count);
    bool rewind();
    void clear();

    bool debug_IsAllJobDone();

protected:
    Buffer<Job*> mJobs;
    u32 mNumJobs;
    u32 mNumProcessedJobs;
    bool _230;
};
}  // namespace sead
