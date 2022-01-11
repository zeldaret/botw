#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include <Havok/Physics2012/Dynamics/Collide/hkpResponseModifier.h>
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include "KingSystem/Physics/System/physMemSystem.h"

namespace ksys::phys {

RigidBody::RigidBody(u32 a, u32 mass_scaling, hkpRigidBody* hk_body, const sead::SafeString& name,
                     sead::Heap* heap, bool a7)
    : mCS(heap), mHkBody(hk_body), mRigidBodyAccessor(hk_body), _b4(a) {
    if (!name.isEmpty()) {
        mHkBody->setName(name.cstr());
    }
    mHkBody->setUserData(reinterpret_cast<hkUlong>(this));
    mHkBody->m_motion.m_savedMotion = nullptr;
    mHkBody->m_motion.m_motionState.m_timeFactor.setOne();
    mHkBody->enableDeactivation(true);
    mHkBody->getCollidableRw()->m_allowedPenetrationDepth = 0.1f;
    if (mFlags.isOff(Flag::MassScaling)) {
        mHkBody->m_responseModifierFlags |= hkpResponseModifier::Flags::MASS_SCALING;
    }

    mFlags.change(Flag::_80, _b4 == 5);
    mFlags.change(Flag::MassScaling, mass_scaling == 1);
    mFlags.change(Flag::_10, a7);
    mFlags.set(Flag::_100);
}

void RigidBody::setMotionFlag(MotionFlag flag) {
    auto lock = sead::makeScopedLock(mCS);

    mMotionFlags.set(flag);

    if (mFlags.isOff(Flag::_20) && mFlags.isOff(Flag::_2)) {
        mFlags.set(Flag::_2);
        MemSystem::instance()->getRigidBodyRequestMgr()->sub_7100FA6C8C(
            mFlags.isOn(Flag::MassScaling), this);
    }
}

bool RigidBody::sub_7100F8D1F8() const {
    return mFlags.isOn(Flag::_8);
}

bool RigidBody::sub_7100F8D204() const {
    return mMotionFlags.isOn(MotionFlag::_1);
}

bool RigidBody::sub_7100F8D210() const {
    return mMotionFlags.isOn(MotionFlag::_2);
}

// NON_MATCHING: mFlags is loaded differently
void RigidBody::sub_7100F8D21C() {
    auto lock = sead::makeScopedLock(mCS);

    if (mMotionFlags.isOn(MotionFlag::_1)) {
        mMotionFlags.reset(MotionFlag::_1);
        mMotionFlags.set(MotionFlag::_2);
    } else if (mFlags.isOn(Flag::_8)) {
        setMotionFlag(MotionFlag::_2);
    }
}

MotionType RigidBody::getMotionInfo() const {
    if (mMotionFlags.isOn(MotionFlag::Dynamic))
        return MotionType::Dynamic;
    if (mMotionFlags.isOn(MotionFlag::Keyframed))
        return MotionType::Keyframed;
    if (mMotionFlags.isOn(MotionFlag::Fixed))
        return MotionType::Fixed;
    return mRigidBodyAccessor.getMotionType();
}

void RigidBody::setContactMask(u32 value) {
    mContactMask.setDirect(value);
}

void RigidBody::setContactAll() {
    mContactMask.makeAllOne();
}

void RigidBody::setContactNone() {
    mContactMask.makeAllZero();
}

}  // namespace ksys::phys
