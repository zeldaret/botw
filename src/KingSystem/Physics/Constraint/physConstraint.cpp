#include "KingSystem/Physics/Constraint/physConstraint.h"
#include <Havok/Physics2012/Dynamics/Constraint/hkpConstraintInstance.h>
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <heap/seadHeap.h>
#include "KingSystem/Physics/Constraint/physConstraintListener.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyRequestMgr.h"
#include "KingSystem/Physics/StaticCompound/physStaticCompoundMgr.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Utils/HeapUtil.h"

namespace ksys::phys {

Constraint::Constraint(hkpConstraintInstance* constraint, RigidBody* parent, RigidBody* child,
                       hkQuaternionf* quat, void* cs_option)
    : mConstraint(constraint), mCsOption(cs_option) {
    mDirection = quat->m_vec[0];
    mSleepingBodies[ConstrainedType::Parent] = parent;
    mSleepingBodies[ConstrainedType::Child] = child;

    mActiveBodies[ConstrainedType::Parent] = System::instance()->getWorldRigidBody();
    mActiveBodies[ConstrainedType::Child] = nullptr;

    mConstraint->setUserData(reinterpret_cast<hkUlong>(this));

    if (constraint->getPriority() == hkpConstraintInstance::PRIORITY_TOI) {
        mFlags.set(Flag::TOIEnabled);
    }
}

void Constraint::sub_7100F69FF0() {
    auto lock = sead::makeScopedLock(mCS);

    if (mSysFlags.isOn(SysFlag::_2)) {
        mSysFlags.reset(SysFlag::_2);
        mSysFlags.set(SysFlag::HasSleepingBodies);
        return;
    }

    if (mSysFlags.isOff(SysFlag::HasSleepingBodies)) {
        pushToSystem();
    }
}

void Constraint::sub_7100F6A074() {
    auto lock = sead::makeScopedLock(mCS);

    if (mSysFlags.isOn(SysFlag::HasSleepingBodies)) {
        mSysFlags.reset(SysFlag::HasSleepingBodies);
        mSysFlags.set(SysFlag::_2);
        return;
    }

    if (mFlags.isOn(Flag::Active)) {
        pushToSystem2();
    }
}

void Constraint::setConstraintWeights(float parent_weight, float child_weight) {
    auto lock = sead::makeScopedLock(mCS);

    if (mSysFlags.isOff(SysFlag::_4)) {
        pushToSystem4();
    }
    mWeightParent = parent_weight;
    mWeightChild = child_weight;
}

void Constraint::pushToSystem() {
    auto lock = sead::makeScopedLock(mCS);
    if (mSysFlags.isZero()) {
        System::instance()->getRigidBodyRequestMgr()->pushConstraint(this);
    }
    mSysFlags.set(SysFlag::HasSleepingBodies);
}

void Constraint::pushToSystem2() {
    auto lock = sead::makeScopedLock(mCS);
    if (mSysFlags.isZero()) {
        System::instance()->getRigidBodyRequestMgr()->pushConstraint(this);
    }
    mSysFlags.set(SysFlag::_2);
}

void Constraint::pushToSystem4() {
    auto lock = sead::makeScopedLock(mCS);
    if (mSysFlags.isZero()) {
        System::instance()->getRigidBodyRequestMgr()->pushConstraint(this);
    }
    mSysFlags.set(SysFlag::_4);
}

void Constraint::pushToSystem8() {
    auto lock = sead::makeScopedLock(mCS);
    if (mSysFlags.isZero()) {
        System::instance()->getRigidBodyRequestMgr()->pushConstraint(this);
    }
    mSysFlags.set(SysFlag::_8);
}

void Constraint::allocConstraintListener(sead::Heap* heap) {
    void* listener_storage = util::allocStorage<ConstraintListener>(heap, 0x10);
    mListener = new (listener_storage) ConstraintListener;
    mConstraint->addConstraintListener(mListener);
}

void Constraint::unlinkIf2Set() {
    auto lock = sead::makeScopedLock(mCS);
    if (mSysFlags.isOn(SysFlag::_2)) {
        unlinkConstrainedBodies(true, true);
    }
}

void Constraint::unlink() {
    unlinkConstrainedBodies(true, true);
}

void Constraint::wake() {
    auto lock = sead::makeScopedLock(mCS);

    if (mFlags.isOn(Flag::Active)) {
        if (mSleepingBodies[ConstrainedType::Parent]) {
            setRigidBody(mActiveBodies[ConstrainedType::Parent],
                         mSleepingBodies[ConstrainedType::Child]);
            mSleepingBodies[ConstrainedType::Parent] = nullptr;
        }
        if (mSleepingBodies[ConstrainedType::Child]) {
            setRigidBody(mActiveBodies[ConstrainedType::Parent],
                         mSleepingBodies[ConstrainedType::Child]);
            mSleepingBodies[ConstrainedType::Child] = nullptr;
        }
    }

    if (mSysFlags.isOn(SysFlag::HasSleepingBodies)) {
        if (checkIsSleeping()) {
            addToWorld(true);
        } else {
            addToWorld(false);
        }
    }

    if (mSysFlags.isOn(SysFlag::_4)) {
        calcMass();
    }
    mSysFlags.makeAllZero();
}

bool Constraint::checkIsSleeping() const {
    return mSleepingBodies[ConstrainedType::Parent] || mSleepingBodies[ConstrainedType::Child];
}

bool Constraint::setRigidBody(RigidBody* existing_body, RigidBody* body) {
    bool result = false;
    if (existing_body != body && body &&
        (System::instance()->getWorldRigidBody() || body->isAddedToWorld())) {
        mFlags.set(Flag::IsModifyingConstrained);

        bool already_active = mFlags.isOn(Flag::Active);

        hkpRigidBody* existing_hk = existing_body ? existing_body->getHkBody() : nullptr;
        hkpRigidBody* body_hk = body->getHkBody();

        if (already_active) {
            System::instance()->removeConstraintFromWorld(mConstraint);
            if (mConstraintParam) {
                System::instance()->removeConstraintParam(mConstraintParam);
            }
            mFlags.reset(Flag::Active);
            mFlags.set(Flag::PendingRemove);
        }

        if (mActiveBodies[ConstrainedType::Parent] == existing_body) {
            mActiveBodies[ConstrainedType::Parent] = body;
        } else if (mActiveBodies[ConstrainedType::Child] == existing_body) {
            mActiveBodies[ConstrainedType::Child] = body;
        }

        mConstraint->replaceEntity(existing_hk, body_hk);
        if (already_active) {
            System::instance()->addConstraintToWorld(mConstraint);
            if (mConstraintParam) {
                System::instance()->addConstraintParam(mConstraintParam);
            }
            mFlags.set(Flag::Active);
            mFlags.reset(Flag::PendingRemove);
        }
        body->setConstraintAttached();

        result = true;
    }
    mFlags.reset(Flag::IsModifyingConstrained);
    return result;
}

bool Constraint::addToWorld(bool restore_sleeping) {
    RigidBody* parent;
    RigidBody* child;

    if (restore_sleeping) {
        if (mSleepingBodies[ConstrainedType::Parent]) {
            parent = mSleepingBodies[ConstrainedType::Parent];
        } else {
            parent = mActiveBodies[ConstrainedType::Parent];
        }
        if (mSleepingBodies[ConstrainedType::Child]) {
            child = mSleepingBodies[ConstrainedType::Child];
        } else {
            child = mActiveBodies[ConstrainedType::Child];
        }
    } else {
        parent = mActiveBodies[ConstrainedType::Parent];
        child = mActiveBodies[ConstrainedType::Child];
    }

    if (child == System::instance()->getWorldRigidBody()) {
        return false;
    }

    if (parent->isSensor()) {
        return false;
    }

    if (child && child->isSensor()) {
        return false;
    }

    if (!parent->isAddedToWorld()) {
        return false;
    }

    if (child && !child->isAddedToWorld()) {
        return false;
    }

    if (mFlags.isOn(Flag::Active)) {
        return false;
    }

    auto lock = sead::makeScopedLock(mSpinLock);

    if (restore_sleeping) {
        if (mSleepingBodies[ConstrainedType::Parent]) {
            setRigidBody(mActiveBodies[ConstrainedType::Parent], parent);
            mSleepingBodies[ConstrainedType::Parent] = nullptr;
        }
        if (mSleepingBodies[ConstrainedType::Child]) {
            setRigidBody(mActiveBodies[ConstrainedType::Child], child);
            mSleepingBodies[ConstrainedType::Child] = nullptr;
        }
    }

    if (mCallback) {
        (**mCallback)(mCallback, this, false);
    }
    System::instance()->addConstraintToWorld(mConstraint);
    if (mConstraintParam) {
        System::instance()->addConstraintParam(mConstraintParam);
    }
    mFlags.set(Flag::Active);
    mFlags.reset(Flag::PendingRemove);
    return true;
}

// NON_MATCHING: float stuff
void Constraint::calcMass() {
    if (mConstraint->getOwner() == nullptr) {
        return;
    }

    auto* parent = mActiveBodies[ConstrainedType::Parent];
    if (parent == nullptr) {
        return;
    }

    auto* child = mActiveBodies[ConstrainedType::Child];
    if (child == nullptr) {
        return;
    }

    const auto* mot_parent = parent->getHkBody()->getMotion();
    const auto* mot_child = child->getHkBody()->getMotion();

    const auto mass_parent = mot_parent->getMass();
    const auto mass_child = mot_child->getMass();

    bool parent_heavier = mot_parent->getMass() < mot_child->getMass();

    const auto effective_mass_parent = mass_parent * mWeightChild;
    const auto effective_mass_child = mass_child * mWeightParent;

    float ratio_b = effective_mass_parent / effective_mass_child;
    if (!parent_heavier) {
        ratio_b = 1.0f;
    }

    float ratio_a = effective_mass_child / effective_mass_parent;
    if (parent_heavier) {
        ratio_a = 1.0f;
    }

    hkVector4f vec_a;
    hkVector4f vec_b;

    vec_a.setAll(ratio_a);
    vec_b.setAll(ratio_b);
    mConstraint->setVirtualMassInverse(vec_b, vec_a);
}

void Constraint::clearRigidBody(ConstrainedType type) {
    auto lock = sead::makeScopedLock(mCS);

    mSleepingBodies[type] = nullptr;
    mSysFlags.reset(SysFlag::_8);
}

// NON_MATCHING: return branch inverted
void Constraint::unlinkConstrainedBodies(bool activate_entity, bool attach_to_world) {
    mSysFlags.reset(SysFlag::_8);
    mSleepingBodies[ConstrainedType::Child] = nullptr;

    bool active = mFlags.isOn(Flag::Active);
    if (active && mConstraint->getOwner() != nullptr) {
        if (active) {
            System::instance()->lockWorld(ContactLayerType::Entity);
        }
        mSpinLock.lock();

        if (activate_entity) {
            if (mActiveBodies[ConstrainedType::Parent])
                mActiveBodies[ConstrainedType::Parent]->getHkBody()->activate();
            if (mActiveBodies[ConstrainedType::Child])
                mActiveBodies[ConstrainedType::Child]->getHkBody()->activate();
        }
        auto* cs = mConstraint;
        System::instance()->getRigidBodyRequestMgr()->removeConstraintFromWorld(cs);

        if (mConstraintParam) {
            System::instance()->removeConstraintParam(mConstraintParam);
        }
        mFlags.set(Flag::PendingRemove);
        mFlags.reset(Flag::Active);
        mSpinLock.unlock();
        if (active) {
            System::instance()->unlockWorld(ContactLayerType::Entity);
        }
        return;
    }

    if (attach_to_world &&
        mActiveBodies[ConstrainedType::Child] != System::instance()->getWorldRigidBody()) {
        if (active) {
            System::instance()->lockWorld(ContactLayerType::Entity);
        }
        mSpinLock.lock();
        if (mActiveBodies[ConstrainedType::Child]) {
            setRigidBody(mActiveBodies[ConstrainedType::Child],
                         System::instance()->getWorldRigidBody());
        }
        mSpinLock.unlock();
        if (active) {
            System::instance()->unlockWorld(ContactLayerType::Entity);
        }
    }
}

bool Constraint::isFlag2Set() const {
    return mSysFlags.isOn(SysFlag::_2);
}

bool Constraint::initParent(RigidBody* body) {
    return initBody(body, ConstrainedType::Parent);
}

bool Constraint::initChild(RigidBody* body) {
    return initBody(body, ConstrainedType::Child);
}

bool Constraint::initBody(RigidBody* body, ConstrainedType type) {
    if (mSysFlags.isOn(SysFlag::_2)) {
        return false;
    }

    auto lock = sead::makeScopedLock(mCS);
    mSleepingBodies[type] = body;
    pushToSystem8();
    return true;
}

bool Constraint::initWithGroup(StaticCompoundRigidBodyGroup* grp) {
    if (grp == nullptr) {
        return false;
    }

    auto* mgr = System::instance()->getStaticCompoundMgr();
    if (mgr == nullptr) {
        return false;
    }

    auto* body = mgr->getRigidBody(grp);
    if (body == nullptr) {
        return false;
    }

    return initChild(body);
}

// NON_MATCHING: stack reg swapped
bool Constraint::initBodies(RigidBody* a, RigidBody* b) {
    bool parent_ok = initParent(a);
    bool child_ok = initChild(b);
    return parent_ok && child_ok;
}

RigidBody* Constraint::getRigidBody(s32 idx) const {
    if (mSleepingBodies[idx]) {
        return mSleepingBodies[idx];
    }
    return mActiveBodies[idx];
}

void Constraint::destroy(Constraint* instance) {
    delete instance;
}

}  // namespace ksys::phys
