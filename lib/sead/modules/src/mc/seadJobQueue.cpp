#include <atomic>

#include "basis/seadRawPrint.h"
#include "framework/seadProcessMeter.h"
#include "mc/seadJobQueue.h"
#include "mc/seadWorker.h"
#include "prim/seadScopedLock.h"

namespace sead
{
// NON_MATCHING
JobQueue::JobQueue()
{
    mCoreEnabled.fill(0);
    mNumDoneJobs = 0;
    mGranularity.fill(8);
}

bool JobQueue::run(u32, u32* finished_jobs, Worker*)
{
    *finished_jobs = 0;
    return true;
}

void JobQueue::runAll(u32* finished_jobs)
{
    const u32 size = getNumJobs();
    *finished_jobs = 0;
    while (true)
    {
        u32 finished_jobs_batch = 0;
        const bool ok = run(size, &finished_jobs_batch, nullptr);
        *finished_jobs += finished_jobs_batch;
        if (ok)
            break;
    }
    SEAD_ASSERT(*finished_jobs == size);
}

bool JobQueue::isAllParticipantThrough() const
{
    for (auto value : mCoreEnabled.mBuffer)
        if (value)
            return false;
    return true;
}

void JobQueue::setGranularity(CoreId core, u32 x)
{
    mGranularity[core] = x ? x : 1;
}

void JobQueue::setGranularity(u32 x)
{
    for (s32 i = 0; i < mGranularity.size(); ++i)
        setGranularity(i, x);
}

// NON_MATCHING: CMP (AND x y), #0 gets optimized into a TST
void JobQueue::setCoreMaskAndWaitType(CoreIdMask mask, SyncType type)
{
    mStatus = Status::_6;
    mMask = mask;
    for (u32 i = 0; i < CoreInfo::getNumCores(); ++i)
    {
        mCoreEnabled[i] = mask.isOn(i);
        mNumDoneJobs = 0;
    }
    mSyncType = type;
}

void JobQueue::FINISH(CoreId core)
{
    std::atomic_thread_fence(std::memory_order_seq_cst);
    mCoreEnabled[core] = 0;
    wait_AT_WORKER();
}

void JobQueue::wait_AT_WORKER()
{
    std::atomic_thread_fence(std::memory_order_seq_cst);

    switch (mSyncType)
    {
    case SyncType::cCore:
        if (!isDone_())
            mFinishEvent.wait();
        break;
    case SyncType::cThread:
        SEAD_ASSERT_MSG(false, "*NOT YET\n");
        if (!isDone_())
            mFinishEvent.wait();
        break;
    default:
        break;
    }
}

void JobQueue::wait()
{
    if (u32(mSyncType) >= 2)
    {
        if (mSyncType != SyncType::cThread)
            return;
        SEAD_ASSERT_MSG(false, "NOT IMPLEMENTED.\n");
    }
    if (!isDone_())
        mFinishEvent.wait();
}

bool JobQueue::isDone_()
{
    return mNumDoneJobs == getNumJobs();
}

// NON_MATCHING: stack
void PerfJobQueue::initialize(const char* name, Heap* heap)
{
    mBars.allocBufferAssert(CoreInfo::getNumCores(), heap);
    mInts.allocBufferAssert(CoreInfo::getNumCores(), heap);

    for (s32 i = 0; i < mInts.size(); ++i)
        mInts[CoreId(i)] = 0;

    for (s32 i = 0; i < mBars.size(); ++i)
        mBars[i].setName(CoreId(i).text());

    mProcessMeterBar.setColor({1, 1, 0, 1});
    mProcessMeterBar.setName(name);
}

void PerfJobQueue::finalize()
{
    mInts.freeBuffer();
    mBars.freeBuffer();
}

void PerfJobQueue::reset()
{
    for (s32 i = 0; i < mInts.size(); ++i)
        mInts[CoreId(i)] = 0;
}

// NON_MATCHING: stack
void PerfJobQueue::measureBeginDeque()
{
    auto& bar = mBars[CoreInfo::getCurrentCoreId()];
    static_cast<void>(mInts[CoreInfo::getCurrentCoreId()]);
    bar.measureBegin(Color4f::cWhite);
}

void PerfJobQueue::measureEndDeque()
{
    mBars[CoreInfo::getCurrentCoreId()].measureEnd();
}

void PerfJobQueue::measureBeginRun()
{
    auto& bar = mBars[CoreInfo::getCurrentCoreId()];
    auto& idx = mInts[CoreInfo::getCurrentCoreId()];
    bar.measureBegin(getBarColor(idx));
    idx = (idx + 1) % 9;
}

void PerfJobQueue::measureEndRun()
{
    mBars[CoreInfo::getCurrentCoreId()].measureEnd();
}

// NON_MATCHING: loading sColors...
const Color4f& PerfJobQueue::getBarColor(u32 idx) const
{
    static const SafeArray<Color4f, 9> sColors = {{
        {0.2078431397676468, 0.8313725590705872, 0.6274510025978088, 1.0},
        {0.0, 0.6666666865348816, 0.4470588266849518, 1.0},
        {0.125490203499794, 0.49803921580314636, 0.3764705955982208, 1.0},
        {0.7490196228027344, 0.5254902243614197, 0.1882352977991104, 1.0},
        {1.0, 0.6000000238418579, 0.0, 1.0},
        {1.0, 0.6980392336845398, 0.250980406999588, 1.0},
        {0.6901960968971252, 0.1725490242242813, 0.29411765933036804, 1.0},
        {0.0, 0.9176470637321472, 0.21568627655506134, 1.0},
        {0.9607843160629272, 0.239215686917305, 0.40784314274787903, 1.0},
    }};
    return sColors.mBuffer[idx];
}

void PerfJobQueue::attachProcessMeter()
{
    if (!ProcessMeter::instance())
        return;

    for (s32 i = 0; i < mBars.size(); ++i)
        ProcessMeter::instance()->attachProcessMeterBar(&mBars[i]);

    ProcessMeter::instance()->attachProcessMeterBar(&mProcessMeterBar);
}

void PerfJobQueue::detachProcessMeter()
{
    if (!ProcessMeter::instance())
        return;

    for (s32 i = 0; i < mBars.size(); ++i)
        ProcessMeter::instance()->detachProcessMeterBar(&mBars[i]);

    ProcessMeter::instance()->detachProcessMeterBar(&mProcessMeterBar);
}

FixedSizeJQ::FixedSizeJQ()
{
    _230 = true;
    mStatus = Status::_0;
    mNumJobs = 0;
    mNumProcessedJobs = 0;
}

void FixedSizeJQ::begin() {}

// TODO: Splatoon 2 and BotW sead have a different implementation which checks _230 and the current
// core number...
bool FixedSizeJQ::run(u32 size, u32* finished_jobs, Worker* worker)
{
    *finished_jobs = 0;

#ifdef SEAD_DEBUG
    mPerf.measureBeginDeque();
#endif
    u32 num_finished = 0;
    // NON_MATCHING: Clang refuses to materialize these variables here...
    bool ret = true;
    s32 begin = 0;
    s32 end = -1;
    if (size > 0 && mNumJobs > 0)
    {
        if (worker)
            worker->setState(Worker::State::cRunning_WaitLock);

        mLock.lock();

        if (worker)
            worker->setState(Worker::State::cRunning_GetLock);

        begin = mNumProcessedJobs;
        const auto num_jobs = mNumJobs;
        num_finished = std::min(num_jobs - begin, size);

        mNumProcessedJobs = num_finished + begin;
        mLock.unlock();
        end = num_finished + begin - 1;
        ret = num_finished + begin >= num_jobs;
    }
#ifdef SEAD_DEBUG
    mPerf.measureEndDeque();
#endif

#ifdef SEAD_DEBUG
    mPerf.measureBeginRun();
#endif
    if (worker)
        worker->setState(Worker::State::cRunning_Run);

    for (s32 i = begin; i <= end; ++i)
        mJobs[i]->invoke();

    if (worker)
        worker->setState(Worker::State::cRunning_AfterRun);
#ifdef SEAD_DEBUG
    mPerf.measureEndRun();
#endif

    if (ret)
    {
        if (worker)
            worker->setState(Worker::State::cRunning_AllJobDoneReturn);
    }
    else
    {
        if (worker)
            worker->setState(Worker::State::cRunning_BeforeReturn);
    }

    *finished_jobs = num_finished;
    return ret;
}

u32 FixedSizeJQ::getNumJobs() const
{
    return mNumJobs;
}

void FixedSizeJQ::initialize(u32 size, Heap* heap)
{
#ifdef SEAD_DEBUG
    mPerf.initialize(getName().cstr(), heap);
#endif

    ScopedLock<JobQueueLock> lock(&mLock);
    mJobs.allocBufferAssert(size, heap);
    mNumJobs = 0;
    mNumProcessedJobs = 0;
    mStatus = Status::_1;
}

void FixedSizeJQ::finalize()
{
#ifdef SEAD_DEBUG
    mPerf.finalize();
#endif
    mJobs.freeBuffer();
}

bool FixedSizeJQ::enque(Job* job)
{
    mStatus = Status::_3;

    if (mNumJobs >= u32(mJobs.size()))
        return false;

    mJobs[mNumJobs++] = job;
    return true;
}

bool FixedSizeJQ::enqueSafe(Job* job)
{
    mStatus = Status::_3;

    ScopedLock<JobQueueLock> lock(&mLock);
    if (mNumJobs >= u32(mJobs.size()))
        return false;

    mJobs[mNumJobs++] = job;
    return true;
}

Job* FixedSizeJQ::deque()
{
    ScopedLock<JobQueueLock> lock(&mLock);

    if (mNumProcessedJobs >= mNumJobs)
        return nullptr;

    return mJobs[mNumProcessedJobs++];
}

u32 FixedSizeJQ::deque(Job** jobs, u32 count)
{
    ScopedLock<JobQueueLock> lock(&mLock);

    u32 ret = 0;
    while (mNumProcessedJobs < mNumJobs && ret < count)
    {
        jobs[ret] = mJobs[mNumProcessedJobs++];
        ++ret;
    }
    return ret;
}

bool FixedSizeJQ::rewind()
{
#ifdef SEAD_DEBUG
    mPerf.reset();
#endif
    mNumProcessedJobs = 0;
    return true;
}

void FixedSizeJQ::clear()
{
    mStatus = Status::_5;
#ifdef SEAD_DEBUG
    mPerf.reset();
#endif
    mNumJobs = 0;
    mNumProcessedJobs = 0;
    mSyncType = SyncType::cNoSync;
}

bool FixedSizeJQ::debug_IsAllJobDone()
{
    return mNumProcessedJobs >= mNumJobs;
}
}  // namespace sead
