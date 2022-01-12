#include "KingSystem/Physics/RigidBody/physRigidBodyMotionProxy.h"
#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include "KingSystem/Physics/physConversions.h"

namespace ksys::phys {

RigidBodyMotionProxy::RigidBodyMotionProxy(RigidBody* body) : MotionAccessor(body) {}

bool RigidBodyMotionProxy::init(const RigidBodyInstanceParam& params, sead::Heap* heap) {
    mMaxLinearVelocity = params.max_linear_velocity;
    mMaxAngularVelocity = params.max_angular_velocity_rad;
    mTimeFactor = params.time_factor;
    return true;
}

KSYS_ALWAYS_INLINE void RigidBodyMotionProxy::setTransformImpl(const sead::Matrix34f& mtx) {
    if (mBody->isFlag8Set()) {  // flag 8 = block updates?
        setMotionFlag(RigidBody::MotionFlag::_20);
        return;
    }

    hkTransformf transform;
    toHkTransform(&transform, mtx);
    mBody->getHkBody()->getMotion()->setTransform(transform);
}

void RigidBodyMotionProxy::setTransform(const sead::Matrix34f& mtx, bool notify) {
    mTransform = mtx;
    setTransformImpl(mtx);
}

void RigidBodyMotionProxy::setPosition(const sead::Vector3f& position, bool notify) {
    if (hasMotionFlagDisabled(RigidBody::MotionFlag::_20)) {
        getTransform(&mTransform);
    }

    mTransform.setTranslation(position);
    setTransformImpl(mTransform);
}

void RigidBodyMotionProxy::getPosition(sead::Vector3f* position) {
    if (hasMotionFlagSet(RigidBody::MotionFlag::_20)) {
        mTransform.getTranslation(*position);
    } else {
        const auto hk_position = getMotion()->getPosition();
        storeToVec3(position, hk_position);
    }
}

void RigidBodyMotionProxy::getRotation(sead::Quatf* rotation) {
    if (hasMotionFlagSet(RigidBody::MotionFlag::_20)) {
        mTransform.toQuat(*rotation);
    } else {
        toQuat(rotation, getMotion()->getRotation());
    }

    rotation->normalize();
}

void RigidBodyMotionProxy::getTransform(sead::Matrix34f* mtx) {
    if (hasMotionFlagSet(RigidBody::MotionFlag::_20)) {
        *mtx = mTransform;
    } else {
        const auto& transform = getMotion()->getTransform();
        setMtxRotation(mtx, transform.getRotation());
        setMtxTranslation(mtx, transform.getTranslation());
    }
}

void RigidBodyMotionProxy::setCenterOfMassInLocal(const sead::Vector3f& center) {
    mCenterOfMassInLocal.e = center.e;

    if (mBody->isFlag8Set()) {
        setMotionFlag(RigidBody::MotionFlag::_800);
        return;
    }

    mBody->getHkBody()->setCenterOfMassLocal(toHkVec4(center));
}

void RigidBodyMotionProxy::getCenterOfMassInLocal(sead::Vector3f* center) {
    if (hasMotionFlagSet(RigidBody::MotionFlag::_800)) {
        center->e = mCenterOfMassInLocal.e;
    } else {
        const auto hk_center = getMotion()->getCenterOfMassLocal();
        storeToVec3(center, hk_center);
    }
}

bool RigidBodyMotionProxy::setLinearVelocity(const sead::Vector3f& velocity, float epsilon) {
    if (velocity.equals(mLinearVelocity, epsilon))
        return false;

    mLinearVelocity.e = velocity.e;
    setMotionFlag(RigidBody::MotionFlag::_40);
    return true;
}

bool RigidBodyMotionProxy::setLinearVelocity(const hkVector4f& velocity, float epsilon) {
    sead::Vector3f vec;
    storeToVec3(&vec, velocity);
    return setLinearVelocity(vec, epsilon);
}

void RigidBodyMotionProxy::getLinearVelocity(sead::Vector3f* velocity) {
    if (hasMotionFlagSet(RigidBody::MotionFlag::_40)) {
        velocity->e = mLinearVelocity.e;
    } else {
        const auto hk_velocity = getMotion()->getLinearVelocity();
        storeToVec3(velocity, hk_velocity);
    }
}

bool RigidBodyMotionProxy::setAngularVelocity(const sead::Vector3f& velocity, float epsilon) {
    if (velocity.equals(mAngularVelocity, sead::Mathf::epsilon()))
        return false;

    mAngularVelocity.e = velocity.e;
    setMotionFlag(RigidBody::MotionFlag::_80);
    return true;
}

bool RigidBodyMotionProxy::setAngularVelocity(const hkVector4f& velocity, float epsilon) {
    sead::Vector3f vec;
    storeToVec3(&vec, velocity);
    return setAngularVelocity(vec, epsilon);
}

void RigidBodyMotionProxy::getAngularVelocity(sead::Vector3f* velocity) {
    if (hasMotionFlagSet(RigidBody::MotionFlag::_80)) {
        velocity->e = mAngularVelocity.e;
    } else {
        const auto hk_velocity = getMotion()->getAngularVelocity();
        storeToVec3(velocity, hk_velocity);
    }
}

void RigidBodyMotionProxy::setMaxLinearVelocity(float max) {
    mMaxLinearVelocity = max;
    setMotionFlag(RigidBody::MotionFlag::_100);
}

float RigidBodyMotionProxy::getMaxLinearVelocity() {
    if (hasMotionFlagSet(RigidBody::MotionFlag::_100))
        return mMaxLinearVelocity;

    return getMotion()->getMotionState()->m_maxLinearVelocity;
}

void RigidBodyMotionProxy::setMaxAngularVelocity(float max) {
    mMaxAngularVelocity = max;
    setMotionFlag(RigidBody::MotionFlag::_100);
}

float RigidBodyMotionProxy::getMaxAngularVelocity() {
    if (hasMotionFlagSet(RigidBody::MotionFlag::_100))
        return mMaxAngularVelocity;

    return getMotion()->getMotionState()->m_maxAngularVelocity;
}

RigidBody* RigidBodyMotionProxy::getLinkedRigidBody() const {
    return mLinkedRigidBody;
}

bool RigidBodyMotionProxy::isFlag40000Set() const {
    return mFlags.isOn(Flag::_40000);
}

void RigidBodyMotionProxy::getRotation(hkQuaternionf* quat) {
    sead::Quatf rotation;
    getRotation(&rotation);
    toHkQuat(quat, rotation);
}

void RigidBodyMotionProxy::setTimeFactor(float factor) {
    mTimeFactor = factor;
    setMotionFlag(RigidBody::MotionFlag::_100);
}

float RigidBodyMotionProxy::getTimeFactor() {
    return mTimeFactor;
}

}  // namespace ksys::phys
