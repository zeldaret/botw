#pragma once

#include <agl/Utils/aglAtomicPtrArray.h>
#include <container/seadOffsetList.h>
#include <container/seadPtrArray.h>
#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <prim/seadBitFlag.h>
#include <prim/seadScopedLock.h>
#include <thread/seadAtomic.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actBaseProc.h"
#include "KingSystem/ActorSystem/actBaseProcJob.h"
#include "KingSystem/ActorSystem/actBaseProcMap.h"
#include "KingSystem/Utils/StrTreeMap.h"
#include "KingSystem/Utils/Types.h"

namespace sead {
class FixedSizeJQ;
template <typename F>
class IFunction;
class WorkerMgr;
}  // namespace sead

namespace ksys::act {

class BaseProcDeleter;
class BaseProcInitializer;
class BaseProcInitializerArgs;
class BaseProcJobLists;
class BaseProcJobQue;

class BaseProcMgr {
    SEAD_SINGLETON_DISPOSER(BaseProcMgr)
    BaseProcMgr();

public:
    class ProcCreateRequest;

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

    using ExtraJobLinkArray = agl::utl::FixedPtrArray<BaseProcJobLink, 512>;

    static void createInstanceAndInit(sead::Heap* heap);
    static u32 getConstant0() { return sConstant0; }
    static u32 getConstant1() { return sConstant1; }
    static u32 getConstant2() { return sConstant2; }
    static u32 getConstant4() { return sConstant4; }

    virtual ~BaseProcMgr();

    void init(sead::Heap* heap, s32 num_job_types, u32 main_thread_id, u32 havok_thread_id1,
              u32 havok_thread_id2, BaseProcInitializerArgs* initializer_args);

    // region BaseProc management

    void generateProcId(u32* id);
    void registerProc(BaseProc& proc);
    void unregisterProc(BaseProc& proc);

    void addToPreDeleteList(BaseProc& proc);
    bool addToUpdateStateList(BaseProc& proc);
    void eraseFromPreDeleteList(BaseProc& proc);
    void eraseFromUpdateStateList(BaseProc& proc);
    void processPreDeleteList();

    void forEachProc(const sead::IDelegate1<BaseProc*>& callback, u32 flags);
    void deleteAllProcs();
    bool hasFinishedDeletingAllProcs();

    // endregion

    bool requestPreDelete(BaseProc& proc);
    void requestUnloadActorParam(void*);

    // region Job processing

    void pushJob(BaseProc& proc, JobType type);
    void pushJobs(BaseProc& proc);
    void eraseJob(BaseProc& proc, JobType type);
    void eraseJobs(BaseProc& proc);

    void processExtraJobsDirectly(JobType type, s32 prio, bool);
    ExtraJobLinkArray& getExtraJobs();
    void swapExtraJobArray();

    void queueExtraJobPush(BaseProcJobLink* job_link);
    void moveExtraJobsToOtherBuffer();
    bool hasExtraJobLink(BaseProcJobLink* job_link, s32 idx);
    void clearExtraJobArrays();

    void pushJobQueues(sead::WorkerMgr* mgr, JobType type, bool);
    bool pushExtraJobsEx(sead::FixedSizeJQ* jq, JobType type, bool, bool);
    bool pushExtraJobsForCurrentTypeAndPrio(sead::FixedSizeJQ* jq, ExtraJobLinkArray& array);
    bool pushPreCalcJobs(sead::FixedSizeJQ* jq, JobType type, s32 prio, bool, bool);

    void setActorJobType(JobType type);
    void setActorJobTypeAndPrio(JobType type, s32 prio, bool);
    void goIdle();
    void clearMode();
    void calc();
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
    bool isAccessingProcSafe(BaseProc* proc, BaseProc* other);

    // region BaseProc creation

    bool requestCreateProc(ProcCreateRequest& req);
    BaseProc* createProc(ProcCreateRequest& req);

    // endregion

    // region Actor initializer control

    void resumeThreadMaybe();
    void stopThreads();
    void clearMessageQueueMaybe();
    void startActorCreateThread();

    void clearInitializerMessageQueuesMaybe();
    s32 getActorCreateInitializerQueueSize();
    s32 getActorCreateInitializerQueueSizeEx(s32 x);
    void invokeOnActorCreateInitializerThreadMaybe(void* delegate);
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
    u32 getNumJobTypes() const { return mNumJobTypes; }

private:
    void doAddToUpdateStateList_(BaseProc& proc);

    sead::CriticalSection* lockProcMap();
    void unlockProcMap();
    void getNextActor(sead::CriticalSection* cs, BaseProc* proc, u32 flags);

    static sead::BufferedSafeString* sResidentActorListStr;
    static u32 sConstant0;
    static u32 sConstant1;
    static u32 sConstant2;
    static u32 sConstant4;

    Status mStatus = Status::Idle;
    util::SizedEnum<JobType, u8> mJobType = JobType::Invalid;
    u8 mCurrentlyProcessingPrio = 8;
    u8 mCounter = 0;
    sead::CriticalSection mProcMapCS;
    sead::OffsetList<BaseProc> mProcPreDeleteList;
    u32 mNumJobTypes = 0;
    BaseProcJobLists* mJobLists = nullptr;
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
    bool mPushActorJobType3InsteadOf6 = false;
    bool mEnableExtraJobPush = false;
    Mode mMode = Mode::_0;
    bool mUnk2 = false;
    bool mIsInitialisingQuestMgrMaybe = false;
    u8 mCurrentExtraJobArrayIdx = 0;
    u8 mUnk3 = 0;
    sead::BitFlag16 mSpecialJobTypesMask = 0;
    u32 mMainThreadId = 0;
    u32 mHavokThreadId1 = 0;
    u32 mHavokThreadId2 = 0;
    u32 mUnk4 = 0;
    sead::SafeArray<ExtraJobLinkArray, 2> mExtraJobLinkArrays{};
};
KSYS_CHECK_SIZE_NX150(BaseProcMgr, 0x21a0);

inline bool BaseProcMgr::addToUpdateStateList(BaseProc& proc) {
    auto lock = sead::makeScopedLock(mProcUpdateStateListCS);
    doAddToUpdateStateList_(proc);
    return (proc.mStateFlags.set(BaseProc::StateFlags::RequestDelete) &
            u32(BaseProc::StateFlags::RequestDelete)) != 0;
}

}  // namespace ksys::act
