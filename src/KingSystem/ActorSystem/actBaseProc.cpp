#include "KingSystem/ActorSystem/actBaseProc.h"
#include <thread/seadThread.h>
#include <time/seadTickSpan.h>
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actBaseProcJobHandler.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/ActorSystem/actBaseProcUnit.h"
#include "KingSystem/Terrain/teraSystem.h"

namespace ksys::act {

BaseProc::BaseProc(const CreateArg& arg)
    : mName(arg.actor_name), mPriority(arg.class_info->priority) {
    BaseProcMgr* mgr = BaseProcMgr::instance();
    mgr->generateProcId(&mId);
    mgr->registerProc(*this);

    mJobHandlers.fill(nullptr);

    BaseProcLinkDataMgr::instance()->acquireLink(this);
}

BaseProcMapNode::~BaseProcMapNode() = default;

BaseProc::~BaseProc() {
    unlinkCalcChild_();
    unlinkCalcParent_();

    if (mUpdateStateListNode.isLinked())
        BaseProcMgr::instance()->eraseFromUpdateStateList(*this);
}

bool BaseProc::init(sead::Heap* heap, bool sleep_after_init) {
    InitContext context;
    context.sleep_after_init = sleep_after_init;
    context.result = InitResult::Skipped;

    if (shouldInit_()) {
        PrepareArg arg;
        if (prepareInit_(heap, arg)) {
            if (context.result != InitResult::Failed)
                context.result = init_();
        } else {
            context.result = InitResult::Failed;
        }
    }

    finalizeInit_(&context);
    return context.result == InitResult::Ok && mStateFlags.isOff(StateFlags::RequestDelete);
}

void BaseProc::sleep(BaseProc::SleepWakeReason reason) {
    if (isDeletedOrDeleting())
        return;

    const auto lock = sead::makeScopedLock(BaseProcMgr::instance()->getProcUpdateStateListCS());

    const bool reason_changed = mFlags.getStorage().setBitOn(int(reason) + 10);
    const auto state = mState;

    bool requested = mStateFlags.reset(StateFlags::RequestWakeUp);
    if (state != State::Sleep)
        requested = BaseProcMgr::instance()->setProcFlag(*this, StateFlags::RequestSleep);

    if (reason_changed || requested)
        onSleepRequested_(reason);
}

void BaseProc::wakeUp(BaseProc::SleepWakeReason reason) {
    if (isDeletedOrDeleting())
        return;

    const auto lock = sead::makeScopedLock(BaseProcMgr::instance()->getProcUpdateStateListCS());

    const bool reason_changed = mFlags.getStorage().setBitOff(int(reason) + 10);
    if (mFlags.isOn(Flags::SleepWakeReasonAny)) {
        if (reason_changed)
            onWakeUpRequested_(reason);
    } else if (isInit() || isSleep()) {
        mStateFlags.reset(StateFlags::RequestSleep);
        bool requested = BaseProcMgr::instance()->setProcFlag(*this, StateFlags::RequestWakeUp);
        if (reason_changed || requested)
            onWakeUpRequested_(reason);
    } else {
        bool cancelled_sleep = mStateFlags.reset(StateFlags::RequestSleep);
        if (reason_changed || cancelled_sleep)
            onWakeUpRequested_(reason);
    }

    if (mProcUnit && !mProcUnit->isParentHandleDefault()) {
        sead::FixedSafeString<0x100> message;
        message.format("BaseProcUnit:%p BaseProc(%s:%p)", mProcUnit, mName.cstr(), this);
    }
}

bool BaseProc::deleteLater(DeleteReason reason) {
    if (isDeletedOrDeleting())
        return false;

    // Debug leftovers?
    mName.cstr();
    mName.cstr();

    BaseProcMgr* mgr = BaseProcMgr::instance();
    const bool is_high_prio = mgr->isHighPriorityThread();

    if (!is_high_prio) {
        mgr->getProcUpdateStateListCS().lock();
        if (isDeletedOrDeleting()) {
            mgr->getProcUpdateStateListCS().unlock();
            return false;
        }
    }

    if (BaseProcMgr::instance()->setProcFlag(*this, StateFlags::RequestDelete))
        onDeleteRequested_(reason);

    if (!is_high_prio)
        mgr->getProcUpdateStateListCS().unlock();

    return true;
}

BaseProc::InitResult BaseProc::init_() {
    return InitResult::Ok;
}

bool BaseProc::shouldInit_() {
    return true;
}

void BaseProc::finalizeInit_(InitContext* context) {
    if (mState == State::Delete)
        return;

    if (context->result != InitResult::Ok) {
        deleteLater(DeleteReason::_1);
        return;
    }

    if (!mProcUnit) {
        if (context->sleep_after_init)
            sleep(SleepWakeReason::_0);
        else
            wakeUp(SleepWakeReason::_0);
    } else {
        sleep(SleepWakeReason::_0);
        if (!mProcUnit->setProc(this))
            deleteLater(DeleteReason::_2);
    }
}

BaseProc::PreDeletePrepareResult BaseProc::prepareForPreDelete_() {
    return PreDeletePrepareResult::Done;
}

// NON_MATCHING: branching
bool BaseProc::startPreparingForPreDelete_() {
    if (mUpdateStateListNode.isLinked())
        return false;

    return !mBaseProcLinkData || mBaseProcLinkData->refCount() <= 0 ||
           BaseProcMgr::instance()->getUnk3() || tera::checkTeraSystemStatus();
}

void BaseProc::destruct_(int should_destruct) {
    if (should_destruct == 1) {
        BaseProcMgr::instance()->eraseFromPreDeleteList(*this);
        BaseProcMgr::instance()->unregisterProc(*this);
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wundefined-bool-conversion"
        // Yes, this check looks strange.
        if (this)
            delete this;
#pragma clang diagnostic pop
    }
}

void BaseProc::onEnterCalc_() {}

void BaseProc::onDeleteRequested_(BaseProc::DeleteReason) {}

void BaseProc::onSleepRequested_(BaseProc::SleepWakeReason) {}

void BaseProc::onWakeUpRequested_(BaseProc::SleepWakeReason) {}

void BaseProc::onEnterDelete_() {}

void BaseProc::onEnterSleep_() {}

void BaseProc::preDelete3_(const PreDeleteArg& arg) {}

bool BaseProc::prepareInit_(sead::Heap*, BaseProc::PrepareArg&) {
    return true;
}

void BaseProc::onPreDeleteStart_(PrepareArg&) {}

void BaseProc::preDelete2_(const PreDeleteArg& arg) {}

void BaseProc::preDelete1_() {}

BaseProc::IsSpecialJobTypeResult BaseProc::isSpecialJobType_(JobType type) {
    if (BaseProcMgr::instance()->isSpecialJobType(type) || isSpecialJobTypeForThisActor_(type))
        return IsSpecialJobTypeResult::Yes;

    return IsSpecialJobTypeResult::No;
}

bool BaseProc::isSpecialJobType(JobType type) {
    if (isSpecialJobType_(type) != IsSpecialJobTypeResult::No)
        return true;

    const auto check = [&](auto self, BaseProc* proc) {
        if (!proc)
            return false;
        const auto result = proc->isSpecialJobType_(type);
        if (result == IsSpecialJobTypeResult::Yes)
            return true;
        if (result == IsSpecialJobTypeResult::_2)
            return false;
        return self(self, proc->mConnectedCalcParent);
    };
    return check(check, mConnectedCalcParent);
}

bool BaseProc::canWakeUp_() {
    return true;
}

void BaseProc::queueExtraJobPush_(JobType type, int idx) {
    if (!isDeletedOrDeleting())
        BaseProcMgr::instance()->queueExtraJobPush(&getJobHandler(type)->getLink());
}

bool BaseProc::shouldSkipJobPush(JobType type) {
    bool skip = mSkippedJobTypesMask.isOnBit(int(type)) || shouldSkipJobPush_(type);

    BaseProc* proc = this;
    while ((proc = proc->mConnectedCalcParent)) {
        if (proc->getState() == State::Delete)
            break;
        skip = proc->mSkippedJobTypesMask.isOnBit(int(type)) || proc->shouldSkipJobPush_(type);
    }
    return skip;
}

inline void BaseProc::setJobPriorityDuringCalc_(BaseProcJobHandler*& handler, JobType type) {
    BaseProcMgr* mgr = BaseProcMgr::instance();
    if (mgr->isPushingJobs() || mgr->getJobType() == type) {
        mgr->setProcFlag(*this, StateFlags::RequestChangeCalcJobPriority);
    } else {
        BaseProcMgr::instance()->eraseJob(*this, type);
        handler->getLink().loadNewPriority();
        handler->getLink().loadNewPriority2();
        BaseProcMgr::instance()->pushJob(*this, type);
    }
}

void BaseProc::setJobPriority(u8 actorparam_priority, JobType type) {
    if (isDeletedOrDeleting())
        return;

    auto& handler = getJobHandler(type);
    handler->getLink().setNewPriority(actorparam_priority);
    if (isCalc()) {
        setJobPriorityDuringCalc_(handler, type);
    } else {
        handler->getLink().loadNewPriority();
    }
}

void BaseProc::setJobPriority2(u8 actorparam_priority, JobType type) {
    if (isDeletedOrDeleting())
        return;

    auto& handler = getJobHandler(type);
    handler->getLink().setNewPriority2(actorparam_priority);
    if (isCalc()) {
        setJobPriorityDuringCalc_(handler, type);
    } else {
        handler->getLink().loadNewPriority2();
    }
}

bool BaseProc::hasJobType_(JobType type) {
    return getJobHandler(type) != nullptr;
}

void BaseProc::afterUpdateState_() {
    mFlags.reset(Flags::_80);
    mFlags.reset(Flags::_100);
}

bool BaseProc::shouldSkipJobPush_(JobType) {
    return false;
}

void BaseProc::onJobPush1_(JobType) {}

void BaseProc::onJobPush2_(JobType) {}

void BaseProc::jobInvoked(JobType type) {
    for (auto* proc = mConnectedCalcParent; proc; proc = proc->mConnectedCalcParent) {
        if (proc->hasJobType_(type))
            return;
    }

    IsSpecialJobTypeResult special;

    if (mStateFlags.isOn(StateFlags::RequestDelete)) {
        if (type == JobType::Calc4)
            getJobHandler(JobType::Calc4)->invoke();
        special = IsSpecialJobTypeResult::Yes;
    } else {
        special = isSpecialJobType_(type);
        auto* handler = getJobHandler(type);
        if (special != IsSpecialJobTypeResult::No)
            handler->invokeSpecial();
        else
            handler->invoke();
    }

    for (auto* child = mConnectedCalcChild; child; child = child->mConnectedCalcChild) {
        if (!child->hasJobType_(type) || !child->isCalc())
            continue;

        const auto child_special = child->isSpecialJobType_(type);
        if (child->mStateFlags.isOn(StateFlags::RequestDelete)) {
            if (type == JobType::Calc4)
                child->getJobHandler(JobType::Calc4)->invoke();
            special = IsSpecialJobTypeResult::Yes;
        } else {
            auto* handler = child->getJobHandler(type);
            if (special == IsSpecialJobTypeResult::Yes ||
                child_special != IsSpecialJobTypeResult::No) {
                handler->invokeSpecial();
                special = child_special != IsSpecialJobTypeResult::No ? child_special :
                                                                        IsSpecialJobTypeResult::Yes;
            } else {
                handler->invoke();
                special = IsSpecialJobTypeResult::No;
            }
        }
    }
}

// NON_MATCHING: branching
bool BaseProc::processStateUpdate(u8 counter) {
    const bool delete_requested = mStateFlags.isOn(StateFlags::RequestDelete);
    const bool initialized = mFlags.isOn(Flags::Initialized);

    if (delete_requested) {
        // Deletion cannot start until the reference count is 0.
        if (initialized && mRefCount.compareExchange(0, -1)) {
            if (mState != State::Delete) {
                BaseProcMgr::instance()->eraseJobs(*this);
                BaseProcMgr::instance()->addToPreDeleteList(*this);
                startDelete_();
            }
            mStateFlags.makeAllZero();
            return true;
        }
        // Try the deletion again later.
        mStateFlags = StateFlags::RequestDelete;
        return false;
    }

    sead::TypedBitFlag<StateFlags> new_flags{mStateFlags};

    if (initialized) {
        if (new_flags.isOn(StateFlags::RequestDeleteProcUnit))
            unlinkProcUnit_();

        if (mStateFlags.isOn(StateFlags::_4000)) {
            if (shouldClearStateFlag4000_())
                new_flags.makeAllZero();
            else
                new_flags = StateFlags::_4000;
        } else {
            new_flags.makeAllZero();
        }

        const auto check_calc_sleep = [&] {
            const bool sleep_requested = mStateFlags.isOn(StateFlags::RequestSleep);
            const State state = mState;
            if (sleep_requested) {
                handleSleepRequest_();
                if (mStateFlags.isAnyOn({StateFlags::RequestWakeUp, StateFlags::_2})) {
                    new_flags.setDirect(mStateFlags.getDirect() &
                                        (u32(StateFlags::RequestWakeUp) | u32(StateFlags::_2)));
                }
                return true;
            }

            const sead::TypedBitFlag<StateFlags> flags{mStateFlags};

            if (state == State::Calc) {
                if (flags.isOn(StateFlags::RequestChangeCalcJobPriority))
                    handleJobPriorityChangeRequest_();
                return true;
            }

            if (!flags.isAnyOn({StateFlags::RequestWakeUp, StateFlags::_2}))
                return true;

            if (canWakeUpOrFlagsSet_()) {
                handleWakeUpRequest_();
                return true;
            }

            return mStateFlags.isOn(StateFlags::RequestSleep);
        };

        if (!check_calc_sleep()) {
            new_flags.setDirect(mStateFlags.getDirect() &
                                (u32(StateFlags::RequestWakeUp) | u32(StateFlags::_2)));
        }

        if (mStateFlags.isOn(StateFlags::RequestDelete)) {
            new_flags.set(StateFlags::RequestDelete);
            mStateFlags = new_flags;
            return false;
        }

        if (mStateFlags.isOn(StateFlags::RequestSleep))
            handleSleepRequest_();

        if (mStateFlags.isOn(StateFlags::RequestResetChild))
            unlinkCalcChild_();

        if (mStateFlags.isOn(StateFlags::RequestResetParent))
            unlinkCalcParent_();

        if (mStateFlags.isOn(StateFlags::RequestSetChild))
            loadNewCalcChild_(counter);

        if (mStateFlags.isOn(StateFlags::RequestSetParent))
            loadNewCalcParent_(counter);
    }

    const bool ret = new_flags.isZero();
    mStateFlags = new_flags;
    return ret;
}

void BaseProc::processPreDelete() {
    if (!mFlags.isOn(Flags::Initialized))
        return;

    if (mFlags.isOn(Flags::PreDeleteFailed)) {
        // Try again.
        if (BaseProcMgr::instance()->requestPreDelete(*this)) {
            mFlags.set(Flags::PreDeleteStarted);
            mFlags.reset(Flags::PreDeleteFailed);
        }

    } else if (!mFlags.isOn(Flags::PreDeleteStarted) && startPreparingForPreDelete_()) {
        mFlags.set(Flags::PreDeleting);
        if (prepareForPreDelete_() == PreDeletePrepareResult::Done) {
            BaseProcLinkDataMgr::instance()->releaseLink(this);
            PrepareArg arg;
            onPreDeleteStart_(arg);

            if (BaseProcMgr::instance()->requestPreDelete(*this))
                mFlags.set(Flags::PreDeleteStarted);
            else
                mFlags.set(Flags::PreDeleteFailed);
        }
    }
}

void BaseProc::freeLinkData() {
    BaseProcLinkDataMgr::instance()->releaseLink(this);
}

void BaseProc::doPreDelete(const PreDeleteArg& arg) {
    preDelete1_();
    preDelete2_(arg);
    preDelete3_(arg);

    if (arg.do_not_destruct_immediately)
        return;

    mFlags.set(Flags::Destructed);
    destruct_(1);
    BaseProcMgr::instance()->decrementPendingDeletions();
}

void BaseProc::unlinkProcUnit_() {
    if (mProcUnit) {
        mProcUnit->unlinkProc(this);
        mProcUnit = nullptr;
    }
}

void BaseProc::unlinkCalcChild_() {
    if (mConnectedCalcChild) {
        mConnectedCalcChild->mConnectedCalcParent = nullptr;
        mConnectedCalcChild = nullptr;
    }
}

void BaseProc::unlinkCalcParent_() {
    auto parent = mConnectedCalcParent;
    if (parent && parent->mConnectedCalcChild) {
        parent->mConnectedCalcChild->mConnectedCalcParent = nullptr;
        parent->mConnectedCalcChild = nullptr;
    }
}

void BaseProc::loadNewCalcChild_(u8 counter) {
    auto child = mConnectedCalcChildNew;
    if (child && !child->isDeletedOrDeleting() && !mConnectedCalcChild &&
        !child->mConnectedCalcParent && !isDeletedOrDeleting() &&
        child->mStateFlags.isOff(StateFlags::RequestDelete)) {
        mConnectedCalcChild = child;
        child->mConnectedCalcParent = this;
        mCounter = counter;
    }
    mConnectedCalcChildNew = nullptr;
}

void BaseProc::loadNewCalcParent_(u8 counter) {
    auto parent = mConnectedCalcParentNew;
    if (parent && !parent->isDeletedOrDeleting() && !parent->mConnectedCalcChild &&
        !mConnectedCalcParent && parent->mStateFlags.isOff(StateFlags::RequestDelete) &&
        !isDeletedOrDeleting()) {
        parent->mConnectedCalcChild = this;
        mConnectedCalcParent = parent;
        parent->mCounter = counter;
    }
    mConnectedCalcParentNew = nullptr;
}

void BaseProc::handleSleepRequest_() {
    if (isDeletedOrDeleting() || mState == State::Sleep)
        return;

    mState = State::Sleep;
    onEnterSleep_();
    BaseProcMgr::instance()->eraseJobs(*this);
}

void BaseProc::handleWakeUpRequest_() {
    if (isDeletedOrDeleting())
        return;

    onEnterCalc_();

    if (!mStateFlags.isOff(StateFlags::RequestDelete))
        return;

    mState = State::Calc;
    BaseProcMgr::instance()->pushJobs(*this);
    unlinkProcUnit_();
}

void BaseProc::handleJobPriorityChangeRequest_() {
    for (u32 i = 0; i < BaseProcMgr::instance()->getNumJobTypes(); ++i) {
        if (!mJobHandlers[i] || !mJobHandlers[i]->getLink().hasPriorityChange())
            continue;

        BaseProcMgr::instance()->eraseJob(*this, JobType(i));
        mJobHandlers[i]->getLink().loadNewPriority();
        mJobHandlers[i]->getLink().loadNewPriority2();
        BaseProcMgr::instance()->pushJob(*this, JobType(i));
    }
}

bool BaseProc::x00000071011ba9fc() {
    if (BaseProcMgr::instance()->getStatus() != BaseProcMgr::Status::ProcessingUpdateStateList)
        return false;

    if (mFlags.isOn(Flags::_80))
        return mFlags.isOn(Flags::_100);

    mFlags.set(Flags::_80);

    if (mFlags.isOff(Flags::Initialized) || mStateFlags.isOn(StateFlags::RequestDelete) ||
        mStateFlags.isOn(StateFlags::RequestSleep) || mStateFlags.isOff(StateFlags::_a) ||
        !canWakeUp_()) {
        return false;
    }

    mFlags.set(Flags::_100);
    return true;
}

bool BaseProc::setStateFlag(u32 flag_bit) {
    return BaseProcMgr::instance()->setProcFlag(*this, flag_bit);
}

bool BaseProc::acquire(ActorLinkConstDataAccess& accessor) {
    if (mState == State::Delete)
        return false;

    if (!BaseProcMgr::instance()->isHighPriorityThread()) {
        int ref_count = std::max(0, mRefCount.load());
        int current_ref_count;
        while (!mRefCount.compareExchange(ref_count, ref_count + 1, &current_ref_count)) {
            if (current_ref_count == -1)
                return false;

            sead::TickSpan span;
            span.setNanoSeconds(1);
            sead::Thread::sleep(span);
            ref_count = current_ref_count;
        }
        accessor.mAcquired = true;
    }

    accessor.mProc = this;
    return true;
}

void BaseProc::release() {
    if (mRefCount >= 1)
        mRefCount--;
}

void BaseProc::startDelete_() {
    BaseProcMgr::instance()->incrementPendingDeletions();

    mState = State::Delete;

    if (mConnectedCalcChildNew) {
        if (mFlags.isOn(Flags::DeleteChildOnDelete))
            mConnectedCalcChildNew->deleteLater(DeleteReason::_18);
        mConnectedCalcChildNew = nullptr;
    }

    if (mConnectedCalcParentNew) {
        if (mFlags.isOn(Flags::DeleteParentOnDelete))
            mConnectedCalcParentNew->deleteLater(DeleteReason::_19);
        mConnectedCalcParentNew = nullptr;
    }

    if (mConnectedCalcChild) {
        if (mFlags.isOn(Flags::DeleteChildOnDelete))
            mConnectedCalcChild->deleteLater(DeleteReason::_16);
        if (mConnectedCalcChild) {
            mConnectedCalcChild->mConnectedCalcParent = nullptr;
            mConnectedCalcChild = nullptr;
        }
    }

    if (mConnectedCalcParent) {
        if (mFlags.isOn(Flags::DeleteParentOnDelete))
            mConnectedCalcParent->deleteLater(DeleteReason::_17);
        if (auto& child = mConnectedCalcParent->mConnectedCalcChild) {
            child->mConnectedCalcParent = nullptr;
            child = nullptr;
        }
    }

    if (mProcUnit) {
        mProcUnit->cleanUp(this, false);
        mProcUnit = nullptr;
    }

    onEnterDelete_();
}

BaseProc* BaseProc::getConnectedCalcParent() const {
    if (mConnectedCalcParent == nullptr || mConnectedCalcParent->mState == State::Delete)
        return nullptr;

    return mConnectedCalcParent;
}

bool BaseProc::setConnectedCalcParent(BaseProc* parent, bool delete_parent_on_delete) {
    if (parent == nullptr)
        return false;

    if (isDeletedOrDeleting() || parent->isDeletedOrDeleting())
        return false;

    if (!BaseProcMgr::instance()->setProcFlag(*this, StateFlags::RequestSetParent))
        return false;

    mConnectedCalcParentNew = parent;

    mFlags.change(Flags::DeleteParentOnDelete, delete_parent_on_delete);

    return true;
}

void BaseProc::resetConnectedCalcParent(bool clear_existing_set_request) {
    if (isDeletedOrDeleting())
        return;

    if (clear_existing_set_request) {
        mStateFlags.reset(StateFlags::RequestSetParent);
        mConnectedCalcParentNew = nullptr;
    }

    if (mConnectedCalcParent)
        BaseProcMgr::instance()->setProcFlag(*this, StateFlags::RequestResetParent);
}

BaseProc* BaseProc::getConnectedCalcChild() const {
    if (!mConnectedCalcChild || mConnectedCalcChild->mState == State::Delete)
        return nullptr;

    return mConnectedCalcChild;
}

bool BaseProc::setConnectedCalcChild(BaseProc* child, bool delete_child_on_delete) {
    if (child == nullptr)
        return false;

    if (isDeletedOrDeleting() || child->isDeletedOrDeleting())
        return false;

    if (!BaseProcMgr::instance()->setProcFlag(*this, StateFlags::RequestSetChild))
        return false;

    mConnectedCalcChildNew = child;

    mFlags.change(Flags::DeleteChildOnDelete, delete_child_on_delete);

    return true;
}

void BaseProc::resetConnectedCalcChild(bool clear_existing_set_request) {
    if (isDeletedOrDeleting())
        return;

    if (clear_existing_set_request) {
        mStateFlags.reset(StateFlags::RequestSetChild);
        mConnectedCalcChildNew = nullptr;
    }

    if (mConnectedCalcChild)
        BaseProcMgr::instance()->setProcFlag(*this, StateFlags::RequestResetChild);
}

void BaseProc::setCreatePriorityState1() {
    mCreatePriorityState = 1;
}

void BaseProc::setCreatePriorityState2() {
    mCreatePriorityState = 2;
}

}  // namespace ksys::act
