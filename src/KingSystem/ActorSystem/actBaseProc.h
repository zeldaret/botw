#pragma once

#include <basis/seadTypes.h>
#include <container/seadListImpl.h>
#include <container/seadSafeArray.h>
#include <container/seadTreeMap.h>
#include <prim/seadBitFlag.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadAtomic.h>
#include "KingSystem/ActorSystem/actBaseProcJob.h"
#include "KingSystem/ActorSystem/actBaseProcMap.h"
#include "KingSystem/Utils/StrTreeMap.h"
#include "KingSystem/Utils/Types.h"

namespace ksys {

namespace act {

class ActorLinkConstDataAccess;
class BaseProc;
class BaseProcLinkData;
class BaseProcJobHandler;
class BaseProcUnit;

class BaseProcHandle {
public:
    BaseProcHandle();
    ~BaseProcHandle();

private:
    BaseProcUnit* mUnit;
    u8 mFlag;
};
KSYS_CHECK_SIZE_NX150(BaseProcHandle, 0x10);

/// Actor base class that encapsulates all the low-level actor lifetime logic.
class BaseProc {
public:
    enum class State : u8 {
        /// The actor is constructed, but not fully initialized yet.
        Init = 0,
        /// The actor is active.
        Calc = 1,
        /// The actor is sleeping: its update jobs won't be run.
        Sleep = 2,
        /// The actor is scheduled for deletion.
        Delete = 3,
    };

    enum class DeleteReason : u32 {
        _0 = 0,
        _1 = 1,
        _2 = 2,
    };

    enum class SleepWakeReason : u32 {
        _0 = 0,
    };

    struct ClassInfo {
        sead::SafeString name;
        u8 priority;
    };
    KSYS_CHECK_SIZE_NX150(ClassInfo, 0x18);

    struct CreateArg {
        const ClassInfo* class_info;
        void* _10;
        u32 _14;
        u32 _18;
        sead::SafeString actor_name;
    };
    KSYS_CHECK_SIZE_NX150(CreateArg, 0x28);

    explicit BaseProc(const CreateArg& arg);
    virtual ~BaseProc();

    SEAD_RTTI_BASE(BaseProc)

    /// @return true iff state is Calc and the actor is not being deleted.
    bool init(sead::Heap* heap, bool sleep_after_init);
    /// Put this actor to sleep. The request is queued.
    void sleep(SleepWakeReason reason);
    /// Wake up this actor. The request is queued.
    void wakeUp(SleepWakeReason reason);
    /// Delete this actor. The request is queued.
    bool deleteLater(DeleteReason reason);
    void freeLinkData();

    u32 getId() const { return mId; }
    const sead::SafeString& getName() const { return mName; }

    u8 getPriority() const { return mPriority; }
    void setPriority(u8 priority) { mPriority = priority; }

    State getState() const { return mState; }
    bool isDeletedOrDeleting() const {
        return mState == State::Delete || mStateFlags.isOn(StateFlags::RequestDelete);
    }

    /// For BaseProcLink or ActorLinkConstDataAccess.
    bool acquire(ActorLinkConstDataAccess& accessor);
    BaseProcLinkData* getBaseProcLinkData() const { return mBaseProcLinkData; }
    /// For BaseProcLink or ActorLinkConstDataAccess.
    void release();

    BaseProc* getConnectedCalcParent() const;
    bool setConnectedCalcParent(BaseProc* parent, bool delete_parent_on_delete);
    void resetConnectedCalcParent(bool clear_existing_set_request);

    BaseProc* getConnectedCalcChild() const;
    void setConnectedCalcChild(BaseProc* child, bool delete_child_on_delete);
    void resetConnectedCalcChild(bool clear_existing_set_request);

    bool isSpecialJobType(JobType type);
    bool shouldSkipJobPush(JobType type);
    void setJobPriority(u8 actorparam_priority, JobType type);
    void setJobPriority2(u8 actorparam_priority, JobType type);

    void setCreatePriorityState2();
    bool setStateFlag(u8 idx);

protected:
    friend class BaseProcLinkDataMgr;
    friend class BaseProcMgr;

    enum class Flags : u32 {
        Initialized = 1,
        PreDeleteStarted = 2,
        PreDeleteFailed = 4,
        Destructed = 8,
        DoNotDelete = 0x10,
        DeleteChildOnDelete = 0x20,
        DeleteParentOnDelete = 0x40,
        _80 = 0x80,
        _100 = 0x100,
        PreDeleting = 0x200,
        SleepWakeReason0 = 0x400,
    };

    enum class StateFlags : u32 {
        RequestDelete = 1,
        _2 = 2,
        RequestSleep = 4,
        RequestWakeUp = 8,
        _a = _2 | RequestWakeUp,
        RequestChangeCalcJobPriority = 0x10,
        _20 = 0x20,
        _40 = 0x40,
        _80 = 0x80,
        RequestSetParent = 0x100,
        RequestSetChild = 0x200,
        RequestResetParent = 0x400,
        RequestResetChild = 0x800,
        _1000 = 0x1000,
        _2000 = 0x2000,
        _4000 = 0x4000,
        RequestDeleteProcUnit = 0x8000,
    };

    enum class InitResult : u32 {
        Ok = 1,
        Failed = 2,
        Skipped = 3,
    };

    enum class PreDeletePrepareResult : u32 {
        NotDone = 0,
        Done = 1,
    };

    enum class IsSpecialJobTypeResult {
        No = 0,
        Yes = 1,
        _2 = 2,
    };

    struct InitContext {
        InitResult result;
        bool sleep_after_init;
    };

    struct PrepareArg {
        bool _0 = false;
        int _4;
    };

    /// Initialize the actor.
    /// @return Ok to keep the actor alive, anything else to kill it?
    virtual InitResult init_();
    /// @return whether prepareInit_ and init_ should be called.
    virtual bool shouldInit_();
    /// Finalize the initialization; the actor is deleted if the result is not Ok.
    virtual void finalizeInit_(InitContext* context);

    /// Called every tick to prepare for pre-delete (after startPreparingForPreDelete_).
    virtual PreDeletePrepareResult prepareForPreDelete_();
    /// Called to start preparing for pre-delete. Return true to allow pre-delete to go ahead.
    virtual bool startPreparingForPreDelete_();

    /// Destructs this actor if should_destruct is 1.
    /// @warning The actor must NOT be used after calling this function.
    virtual void destruct_(int should_destruct);

    /// Called when entering the Calc state.
    virtual void onEnterCalc_();

    /// Called when a new delete operation is queued.
    virtual void onDeleteRequested_(DeleteReason reason);
    /// Called when a new sleep operation is queued.
    virtual void onSleepRequested_(SleepWakeReason reason);
    /// Called when a new wakeup operation is queued.
    virtual void onWakeUpRequested_(SleepWakeReason reason);

    virtual bool shouldClearStateFlag4000_() { return true; }

    /// Called when entering the Delete state.
    virtual void onEnterDelete_();
    /// Called when entering the Sleep state.
    virtual void onEnterSleep_();

    /// Called to actually pre-delete (third and final callback).
    virtual void preDelete3_(bool* do_not_destruct_immediately);

    virtual bool prepareInit_(sead::Heap* heap, PrepareArg& arg);

    /// Called when pre-delete actually starts (after preparation, before requesting it).
    virtual void onPreDeleteStart_(PrepareArg&);
    /// Called to actually pre-delete (second callback).
    virtual void preDelete2_(bool* do_not_destruct_immediately);
    /// Called to actually pre-delete (first callback).
    virtual void preDelete1_();

    virtual IsSpecialJobTypeResult isSpecialJobType_(JobType type);
    virtual bool canWakeUp_();
    virtual void queueExtraJobPush_(JobType type);
    virtual bool hasJobType_(JobType type);
    /// Called after processStateUpdate() is called for all actors in the update state list.
    virtual void afterUpdateState_();

    virtual bool shouldSkipJobPush_(JobType type);
    /// Called before pushing a job with the specified job type (first callback).
    virtual void onJobPush1_(JobType type);
    /// Called before pushing a job with the specified job type (second and final callback).
    virtual void onJobPush2_(JobType type);

    bool processStateUpdate(u8 counter);
    void processPreDelete();
    /// Actually pre-delete the actor. Called from BaseProcDeleter.
    void doPreDelete(bool* do_not_destruct_immediately);
    void startDelete_();

    /// Called from BaseProcMgr when a job for this process is invoked.
    void jobInvoked(JobType type);

    bool isSpecialJobTypeForThisActor_(JobType type) const {
        return mSpecialJobTypesMask.isOnBit(int(type));
    }

    bool x00000071011ba9fc();

    sead::FixedSafeString<64> mName;
    u32 mId = -1;
    State mState = State::Init;
    u8 mPriority = 0;
    u8 mCreatePriorityState = 0;
    u8 mCounter = 0;
    BaseProcLinkData* mBaseProcLinkData = nullptr;
    sead::BitFlag16 mSkippedJobTypesMask;
    sead::BitFlag16 mSpecialJobTypesMask;
    sead::TypedBitFlag<Flags, sead::Atomic<u32>> mFlags;
    sead::TypedBitFlag<StateFlags, sead::Atomic<u32>> mStateFlags;
    BaseProc* mConnectedCalcParent = nullptr;
    BaseProc* mConnectedCalcChild = nullptr;
    BaseProc* mConnectedCalcParentNew = nullptr;
    BaseProc* mConnectedCalcChildNew = nullptr;
    sead::SafeArray<BaseProcJobHandler*, 7> mJobHandlers{};
    sead::Delegate<BaseProc> mInvoker;  // TODO: is this correct?
    sead::ListNode mPostDeleteListNode;
    sead::ListNode mDeleteListNode;
    BaseProcMapNode mMapNode{this};
    BaseProcUnit* mProcUnit = nullptr;
    sead::Atomic<u32> mRefCount = 0;

private:
    void unlinkProcUnit_();
    void unlinkCalcChild_();
    void unlinkCalcParent_();
    void loadNewCalcChild_(u8 counter);
    void loadNewCalcParent_(u8 counter);

    void handleSleepRequest_();
    void handleWakeUpRequest_();
    void handleJobPriorityChangeRequest_();

    bool canWakeUpOrFlagsSet_() {
        return mFlags.isOn(Flags::_80) ? mFlags.isOn(Flags::_100) : canWakeUp_();
    }
};
KSYS_CHECK_SIZE_NX150(BaseProc, 0x180);

}  // namespace act

}  // namespace ksys
