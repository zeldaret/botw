#include "KingSystem/ActorSystem/actBaseProc.h"
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

    if (mDeleteListNode.isLinked())
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

    if (!BaseProcMgr::instance()->addToUpdateStateList(*this, StateFlags::RequestDelete))
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
    if (mDeleteListNode.isLinked())
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

void BaseProc::preDelete3_(bool*) {}

bool BaseProc::prepareInit_(sead::Heap*, BaseProc::PrepareArg&) {
    return true;
}

void BaseProc::onPreDeleteStart_(PrepareArg&) {}

void BaseProc::preDelete2_(bool*) {}

void BaseProc::preDelete1_() {}

BaseProc::IsSpecialJobTypeResult BaseProc::isSpecialJobType_(JobType type) {
    if (BaseProcMgr::instance()->isSpecialJobType(type) || isSpecialJobTypeForThisActor_(type))
        return IsSpecialJobTypeResult::Yes;

    return IsSpecialJobTypeResult::No;
}

bool BaseProc::canWakeUp_() {
    return true;
}

void BaseProc::queueExtraJobPush_(JobType type) {
    if (!isDeletedOrDeleting())
        BaseProcMgr::instance()->queueExtraJobPush(&mJobHandlers[int(type)]->getLink());
}

bool BaseProc::hasJobType_(JobType type) {
    return mJobHandlers[int(type)] != nullptr;
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

void BaseProc::doPreDelete(bool* do_not_destruct_immediately) {
    preDelete1_();
    preDelete2_(do_not_destruct_immediately);
    preDelete3_(do_not_destruct_immediately);

    if (*do_not_destruct_immediately)
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

BaseProc* BaseProc::getConnectedCalcParent() const {
    if (!this->mConnectedCalcParent || this->mConnectedCalcParent->mState == State::Delete) {
        return NULL;
    } else {
        return this->mConnectedCalcParent;
    }
}

bool BaseProc::setConnectedCalcParent(BaseProc* parent, bool delete_parent_on_delete) {

    if (parent == NULL)
        return false;
    
    if (this->isDeletedOrDeleting() || parent->isDeletedOrDeleting()) {
        return false;
    }

    if (!BaseProcMgr::instance()->addToUpdateStateList(*this, StateFlags::RequestSetParent)) {
        return false;
    }

    this->mConnectedCalcParentNew = parent;
    
    this->mFlags.change(Flags::DeleteParentOnDelete, delete_parent_on_delete);

    return true;
}

}  // namespace ksys::act
