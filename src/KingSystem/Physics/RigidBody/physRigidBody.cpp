#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physMemSys.h"

namespace ksys::phys {

// NON_MATCHING
RigidBody::RigidBody(u32 a, u32 mass_scaling, hkpRigidBody* hk_body, const sead::SafeString& name,
                     sead::Heap* heap, bool a7)
    : mHkBody(hk_body), mHkBodyMgr(hk_body), _b4(a) {
    if (!name.isEmpty()) {
        hk_body->setName(name.cstr());
    }
    hk_body->setUserData((intptr_t)this);
    hk_body->m_motion._128 = nullptr;
    hk_body->m_motion.m_motionState__m_timeFactor.setOne();
    hk_body->enableDeactivation(true);
    hk_body->_88 = 0.1f;
    if (mFlags.isOn(Flag1::MassScaling)) {
        hk_body->_132 |= 1;
    }

    if (_b4 == 5) {
        mFlags.set(Flag1::_80);
    } else {
        mFlags.reset(Flag1::_80);
    }
    if (mass_scaling == 1) {
        mFlags.set(Flag1::MassScaling);
    } else {
        mFlags.reset(Flag1::MassScaling);
    }
    if (a7) {
        mFlags.set(Flag1::_10);
    } else {
        mFlags.reset(Flag1::_10);
    }
    mFlags.set(Flag1::_100);
}

void RigidBody::setMotionFlag(MotionFlag flag) {
    auto lock = sead::makeScopedLock(mCS);

    mMotionFlags.set(flag);

    if (mFlags.isOff(Flag1::_20) && mFlags.isOff(Flag1::_2)) {
        mFlags.set(Flag1::_2);
        PhysicsMemSys::instance()->_160->sub_7100FA6C8C(mFlags.isOn(Flag1::MassScaling), this);
    }
}

u32 RigidBody::sub_7100F8D1F8() const {
    return mFlags.isOn(Flag1::_8);
}

u32 RigidBody::sub_7100F8D204() const {
    return mMotionFlags.isOn(MotionFlag::_1);
}

u32 RigidBody::sub_7100F8D210() const {
    return mMotionFlags.isOn(MotionFlag::_2);
}

// NON_MATCHING: mFlags is loaded differently
void RigidBody::sub_7100F8D21C() {
    auto lock = sead::makeScopedLock(mCS);

    if (mMotionFlags.isOn(MotionFlag::_1)) {
        mMotionFlags.reset(MotionFlag::_1);
        mMotionFlags.set(MotionFlag::_2);
    } else if (mFlags.isOn(Flag1::_8)) {
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
    return mHkBodyMgr.getMotionInfo();
}

void RigidBody::setContactMask(u32 value) {
    mContactMask = value;
}

void RigidBody::setContactAll() {
    mContactMask = 0xFFFFFFFF;
}

void RigidBody::setContactNone() {
    mContactMask = 0;
}

}  // namespace ksys::phys
