#pragma once

#include <agl/Utils/aglAtomicPtrArray.h>
#include <container/seadBuffer.h>
#include <container/seadOffsetList.h>
#include <container/seadPtrArray.h>
#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <prim/seadBitFlag.h>
#include <prim/seadScopedLock.h>
#include <prim/seadSizedEnum.h>
#include <prim/seadStorageFor.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadAtomic.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actBaseProc.h"
#include "KingSystem/ActorSystem/actBaseProcJob.h"
#include "KingSystem/ActorSystem/actBaseProcMap.h"
#include "KingSystem/Utils/StrTreeMap.h"
#include "KingSystem/Utils/Thread/Task.h"
#include "KingSystem/Utils/Types.h"

namespace sead {
class FixedSizeJQ;
class WorkerMgr;
}  // namespace sead

namespace ksys::act {

class ActorParam;
class BaseProcCreateTaskData;
class BaseProcDeleter;
class BaseProcInitializer;
struct BaseProcInitializerArgs;
class BaseProcJobLists;
class BaseProcJobQue;

struct BaseProcCreateRequest {
    u32 task_lane_id;
    BaseProcCreateTaskData* task_data;
    util::TaskRemoveCallback* task_remove_callback;
};

class BaseProcMgr {
    SEAD_SINGLETON_DISPOSER(BaseProcMgr)
    BaseProcMgr();

public:
    enum class Status : u8 {
        Idle = 0,
        _1 = 1,
        ProcessingActorJobs = 2,
        ProcessingPreDeleteList = 3,
        ProcessingUpdateStateList = 4,
    };

    enum class Mode : u8 {
        _0 = 0,
    };

    enum class ProcFilter {
        Sleeping = 1 << 0,
        DeletedOrDeleting = 1 << 1,
        Initializing = 1 << 2,
        SkipAccessCheck = 1 << 3,
        _10 = 1 << 4,
        Deleting = 1 << 5,
        Uninitialized = 1 << 6,
    };

    using ProcFilters = sead::TypedBitFlag<ProcFilter>;
    using ExtraJobLinkArray = agl::utl::FixedPtrArray<BaseProcJobLink, 512>;

    /// Wrapper to simplify BaseProc iteration.
    class ProcIteratorContext {
    public:
        ProcIteratorContext(BaseProcMgr& mgr, ProcFilters filters)
            : mMgr(mgr), mCS(mgr.lockProcMap()), mFilters(filters) {}
        ~ProcIteratorContext() { mMgr.unlockProcMap(); }
        BaseProc* next() { return mProc = mMgr.getNextProc(mCS, mProc, mFilters); }

    private:
        BaseProcMgr& mMgr;
        sead::CriticalSection* mCS{};
        ProcFilters mFilters{};
        BaseProc* mProc{};
    };

    static u32 getConstant0() { return sConstant0; }
    static u32 getConstant1() { return sConstant1; }
    static u32 getConstant2() { return sConstant2; }
    static u32 getConstant4() { return sConstant4; }

    virtual ~BaseProcMgr();

    void init(sead::Heap* heap, s32 num_job_types, u32 main_thread_id, u32 havok_thread_id1,
              u32 havok_thread_id2, const BaseProcInitializerArgs& initializer_args);

    // region BaseProc management

    void generateProcId(u32* id);
    void registerProc(BaseProc& proc);
    void unregisterProc(BaseProc& proc);

    void addToPreDeleteList(BaseProc& proc);
    /// @return whether the flag was not set prior to this call and is now set.
    bool setProcFlag(BaseProc& proc, BaseProc::StateFlags flag);
    /// @return whether the flag was not set prior to this call and is now set.
    bool setProcFlag(BaseProc& proc, u32 flag_bit);
    void eraseFromPreDeleteList(BaseProc& proc);
    void eraseFromUpdateStateList(BaseProc& proc);
    void processPreDeleteList();

    // endregion

    bool requestPreDelete(BaseProc& proc);
    void requestUnloadActorParam(ActorParam* param);

    // region Job processing

    void pushJob(BaseProc& proc, JobType type);
    void pushJobs(BaseProc& proc);
    void eraseJob(BaseProc& proc, JobType type);
    void eraseJobs(BaseProc& proc);

    void processExtraJobsDirectly(JobType type, s32 prio, bool);
    ExtraJobLinkArray& getExtraJobs();
    void swapExtraJobArray();

    void queueExtraJobPush(BaseProcJobLink* job_link);
    void moveExtraJobsToOtherBuffer(JobType type);
    bool hasExtraJobLink(BaseProcJobLink* job_link, s32 idx);
    void clearExtraJobArrays();

    void pushJobQueues(sead::WorkerMgr* mgr, JobType type, bool x);
    bool pushExtraJobsEx(sead::FixedSizeJQ* jq, JobType type, u8 priority, bool x, bool y);
    bool pushExtraJobsForCurrentTypeAndPrio(sead::FixedSizeJQ* jq, ExtraJobLinkArray* array);
    bool pushPreCalcJobs(sead::FixedSizeJQ* jq, JobType type, u8 prio, bool x, bool y);

    void setJobType(JobType type);
    void setActorJobTypeAndPrio(JobType type, s32 prio, bool);
    void goIdle();
    void calc();
    void clearMode();
    sead::CriticalSection* lockProcMap();
    void unlockProcMap();
    void deleteAllProcs();
    bool hasFinishedDeletingAllProcs();
    void jobInvoked(BaseProcJobLink* link, s32 required_calc_rounds);

    // endregion

    // region Special job types

    bool isSpecialJobType(JobType type) const;
    void addSpecialJobTypes(u16 mask);
    void removeSpecialJobTypes(u16 mask);

    // endregion

    /// Returns true if and only if the calling thread is the game thread or a Havok thread.
    bool isHighPriorityThread() const;
    /// Returns true if and only if it is safe to access the specified BaseProc.
    bool isAccessingProcSafe(BaseProc* proc, BaseProc* other) const;

    // region BaseProc creation

    bool requestCreateProc(const BaseProcCreateRequest& req);
    BaseProc* createProc(const BaseProcCreateRequest& req);

    // endregion

    // region BaseProc iteration

    BaseProc* getNextProc(sead::CriticalSection* cs, BaseProc* current_proc, ProcFilters filters);
    BaseProc* getProc(const sead::SafeString& name, ProcFilters filters);
    BaseProc* getProc(const u32& id, ProcFilters filters);
    void forEachProc(sead::IDelegate1<BaseProc*>& callback, ProcFilters filters);
    void forEachProc(const sead::SafeString& proc_name, sead::IDelegate1<BaseProc*>& callback,
                     ProcFilters filters);
    ProcIteratorContext getProcs(ProcFilter filters) { return {*this, filters}; }
    bool checkFilters(BaseProc* proc, ProcFilters filters) const;

    // endregion

    // region Actor initializer control

    bool areInitializerThreadsIdle() const;
    void waitForInitializerQueueToEmpty();
    void cancelInitializerTasks();
    void blockInitializerTasks();
    void restartInitializerThreads();
    void pauseInitializerThreads();
    void resumeInitializerThreads();
    void unblockInitDeleteTasks();
    void pauseInitializerMainThread();
    void resumeInitializerMainThread();
    bool isAnyInitializerThreadActive() const;
    int getInitializerQueueSize() const;
    int getInitializerQueueSizeEx(int x = -1) const;
    void removeInitializerTasksIf(sead::IDelegate1R<util::Task*, bool>& predicate);
    void setActorGenerationEnabled(bool enabled);

    // endregion

    auto getUnk3() const { return mUnk3; }
    void incrementUnk3();
    void decrementUnk3();

    void writeResidentActorsCsv(const sead::SafeString& file_path);

    auto& getProcUpdateStateListCS() { return mProcUpdateStateListCS; }

    void incrementPendingDeletions() { mNumPendingDeletions.increment(); }
    void decrementPendingDeletions() { mNumPendingDeletions.decrement(); }

    Status getStatus() const { return mStatus; }
    JobType getJobType() const { return mJobType; }
    u32 getNumJobTypes() const { return mJobLists.size(); }
    BaseProcJobLists& getJobLists(JobType type) { return mJobLists[u32(type)]; }
    bool isPushingJobs() const { return mIsPushingJobs; }

    static u32 sConstant0;
    static u32 sConstant1;
    static u32 sConstant2;
    static u32 sConstant4;

private:
    void doAddToUpdateStateList_(BaseProc& proc);

    bool checkJobPushState() const;

    static sead::BufferedSafeString* sResidentActorListStr;

    Status mStatus = Status::Idle;
    sead::SizedEnum<JobType, u8> mJobType = JobType::Invalid;
    u8 mCurrentlyProcessingPrio = 8;
    u8 mCounter = 0;
    sead::CriticalSection mProcMapCS;
    sead::OffsetList<BaseProc> mProcPreDeleteList;
    sead::Buffer<BaseProcJobLists> mJobLists;
    BaseProcMap mProcMap;
    sead::OffsetList<BaseProc> mProcUpdateStateList;
    sead::CriticalSection mProcUpdateStateListCS;
    sead::CriticalSection mProcPreDeleteListCS;
    BaseProcMapNode* mLastProcMapNode = nullptr;
    BaseProcJobQue* mProcJobQue = nullptr;
    sead::Atomic<u32> mCreatedProcCounter = 0;
    sead::Atomic<u32> mNumPendingDeletions = 0;
    BaseProcInitializer* mProcInitializer = nullptr;
    BaseProcDeleter* mProcDeleter = nullptr;
    bool mIsPushingJobs = false;
    sead::Atomic<bool> mPushActorJobType3InsteadOf6 = false;
    bool mEnableExtraJobPush = false;
    Mode mMode = Mode::_0;
    bool mUnk2 = false;
    bool mIsInitialisingQuestMgrMaybe = false;
    s8 mCurrentExtraJobArrayIdx = 0;
    u8 mUnk3 = 0;
    sead::BitFlag16 mSpecialJobTypesMask = 0;
    u32 mMainThreadId = 0;
    u32 mHavokThreadId1 = 0;
    u32 mHavokThreadId2 = 0;
    u32 mUnk4 = 0;
    sead::StorageFor<sead::SafeArray<ExtraJobLinkArray, 2>> mExtraJobLinkArrays{
        sead::ZeroInitializeTag{}};
};
KSYS_CHECK_SIZE_NX150(BaseProcMgr, 0x21a0);

constexpr auto operator|(BaseProcMgr::ProcFilter a, BaseProcMgr::ProcFilter b) {
    return BaseProcMgr::ProcFilter(u32(a) | u32(b));
}

inline bool BaseProcMgr::setProcFlag(BaseProc& proc, BaseProc::StateFlags flag) {
    auto lock = sead::makeScopedLock(mProcUpdateStateListCS);
    doAddToUpdateStateList_(proc);
    return proc.mStateFlags.set(flag);
}

inline bool BaseProcMgr::setProcFlag(BaseProc& proc, u32 flag_bit) {
    auto lock = sead::makeScopedLock(mProcUpdateStateListCS);
    doAddToUpdateStateList_(proc);
    return proc.mStateFlags.getStorage().setBitOn(flag_bit);
}

}  // namespace ksys::act
