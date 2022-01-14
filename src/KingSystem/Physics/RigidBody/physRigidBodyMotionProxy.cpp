#include "KingSystem/Physics/RigidBody/physRigidBodyMotionProxy.h"
#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include "KingSystem/Physics/RigidBody/physRigidBodyMotion.h"
#include "KingSystem/Physics/physConversions.h"

namespace ksys::phys {

RigidBodyMotionProxy::RigidBodyMotionProxy(RigidBody* body) : MotionAccessor(body) {}

RigidBodyMotionProxy::~RigidBodyMotionProxy() {
    resetLinkedRigidBody();
}

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

void RigidBodyMotionProxy::setTransform(const sead::Matrix34f& mtx,
                                        bool propagate_to_linked_motions) {
    mTransform = mtx;
    setTransformImpl(mtx);
}

void RigidBodyMotionProxy::setPosition(const sead::Vector3f& position,
                                       bool propagate_to_linked_motions) {
    if (hasMotionFlagDisabled(RigidBody::MotionFlag::_20)) {
        getTransform(&mTransform);
    }

    mTransform.setTranslation(position);
    setTransformImpl(mTransform);
}

void RigidBodyMotionProxy::setTransformFromLinkedBody(const sead::Matrix34f& mtx) {
    if (mFlags.isOff(Flag::_80000) && mFlags.isOff(Flag::_100000)) {
        setTransform(mtx, false);
        return;
    }

    sead::Matrix34f new_mtx = mtx;

    sead::Vector3f translate;
    if (mFlags.isOn(Flag::_80000)) {
        translate.setMul(mtx, mLinkedBodyExtraTranslate);
    } else {
        mtx.getTranslation(translate);
    }

    if (mFlags.isOn(Flag::_100000)) {
        sead::Quatf quat;
        mtx.toQuat(quat);
        quat *= mLinkedBodyExtraRotate;
        new_mtx.fromQuat(quat);
    }

    // This must be done after fromQuat() because fromQuat resets the translation component.
    new_mtx.setTranslation(translate);
    setTransform(new_mtx, false);
}

static void makeSRT(sead::Matrix34f& o, const sead::Vector3f& s, const sead::Quatf& r,
                    const sead::Vector3f& t) {
    const float yy = 2 * r.y * r.y;
    const float zz = 2 * r.z * r.z;
    const float xx = 2 * r.x * r.x;
    const float xy = 2 * r.x * r.y;
    const float xz = 2 * r.x * r.z;
    const float yz = 2 * r.y * r.z;
    const float wz = 2 * r.w * r.z;
    const float wx = 2 * r.w * r.x;
    const float wy = 2 * r.w * r.y;

    o.m[0][0] = s.x * (1 - yy - zz);
    o.m[0][1] = s.y * (xy - wz);
    o.m[0][2] = s.z * (xz + wy);

    o.m[1][0] = s.x * (xy + wz);
    o.m[1][1] = s.y * (1 - xx - zz);
    o.m[1][2] = s.z * (yz - wx);

    o.m[2][0] = s.x * (xz - wy);
    o.m[2][1] = s.y * (yz + wx);
    o.m[2][2] = s.z * (1 - xx - yy);

    o.m[0][3] = t.x;
    o.m[1][3] = t.y;
    o.m[2][3] = t.z;
}

static sead::Matrix34f makeSRT(const hkVector4f& s, const hkQuaternionf& r, const hkVector4f& t) {
    sead::Vector3f ss;
    toVec3(&ss, s);

    sead::Quatf rr;
    toQuat(&rr, r);

    sead::Vector3f tt;
    toVec3(&tt, t);

    sead::Matrix34f o;
    makeSRT(o, ss, rr, tt);
    return o;
}

static sead::Matrix34f makeRT(const hkQuaternionf& r, const hkVector4f& t) {
    return makeSRT(hkVector4f::getConstant<HK_QUADREAL_1>(), r, t);
}

// NON_MATCHING: two fmul instructions reordered in sead::Matrix34f mtx = makeRT(...)
void RigidBodyMotionProxy::setTransformFromLinkedBody(const hkVector4f& hk_translate,
                                                      const hkQuaternionf& hk_rotate) {
    if (mFlags.isOff(Flag::_80000) && mFlags.isOff(Flag::_100000)) {
        setTransform(makeRT(hk_rotate, hk_translate), false);
        return;
    }

    sead::Matrix34f mtx = makeRT(hk_rotate, hk_translate);

    sead::Vector3f translate;
    if (mFlags.isOn(Flag::_80000)) {
        translate.setMul(mtx, mLinkedBodyExtraTranslate);
    } else {
        storeToVec3(&translate, hk_translate);
    }

    if (mFlags.isOn(Flag::_100000)) {
        sead::Quatf quat;
        toQuat(&quat, hk_rotate);
        quat *= mLinkedBodyExtraRotate;
        mtx.fromQuat(quat);
    }

    mtx.setTranslation(translate);
    setTransform(mtx, false);
}

void RigidBodyMotionProxy::getPosition(sead::Vector3f* position) {
    if (hasMotionFlagSet(RigidBody::MotionFlag::_20)) {
        mTransform.getTranslation(*position);
    } else {
        const auto hk_position = getRigidBodyMotion()->getPosition();
        storeToVec3(position, hk_position);
    }
}

void RigidBodyMotionProxy::getRotation(sead::Quatf* rotation) {
    if (hasMotionFlagSet(RigidBody::MotionFlag::_20)) {
        mTransform.toQuat(*rotation);
    } else {
        toQuat(rotation, getRigidBodyMotion()->getRotation());
    }

    rotation->normalize();
}

void RigidBodyMotionProxy::getTransform(sead::Matrix34f* mtx) {
    if (hasMotionFlagSet(RigidBody::MotionFlag::_20)) {
        *mtx = mTransform;
    } else {
        const auto& transform = getRigidBodyMotion()->getTransform();
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
        const auto hk_center = getRigidBodyMotion()->getCenterOfMassLocal();
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
        const auto hk_velocity = getRigidBodyMotion()->getLinearVelocity();
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
        const auto hk_velocity = getRigidBodyMotion()->getAngularVelocity();
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

    return getRigidBodyMotion()->getMotionState()->m_maxLinearVelocity;
}

void RigidBodyMotionProxy::setMaxAngularVelocity(float max) {
    mMaxAngularVelocity = max;
    setMotionFlag(RigidBody::MotionFlag::_100);
}

float RigidBodyMotionProxy::getMaxAngularVelocity() {
    if (hasMotionFlagSet(RigidBody::MotionFlag::_100))
        return mMaxAngularVelocity;

    return getRigidBodyMotion()->getMotionState()->m_maxAngularVelocity;
}

void RigidBodyMotionProxy::setLinkedRigidBody(RigidBody* body) {
    auto lock = mBody->makeScopedLock(mBody->isFlag8Set());

    if (mLinkedRigidBody == body)
        return;

    if (mLinkedRigidBody) {
        // If we already have a linked rigid body, unlink it first.
        mLinkedRigidBody->getMotionAccessorForProxy()->deregisterAccessor(this);
        mLinkedRigidBody = nullptr;
    }

    if (body) {
        if (!body->hasFlag(RigidBody::Flag::MassScaling) &&
            mFlags.isOff(Flag::HasLinkedRigidBodyWithoutFlag10)) {
            RigidBodyMotion* accessor = body->getMotionAccessorForProxy();
            if (accessor && accessor->registerAccessor(this)) {
                mLinkedRigidBody = body;
                if (mBody->hasFlag(RigidBody::Flag::_10))
                    mFlags.reset(Flag::HasLinkedRigidBodyWithoutFlag10);
                else
                    mFlags.set(Flag::HasLinkedRigidBodyWithoutFlag10);
            }
        }
    } else {
        mLinkedRigidBody = nullptr;
        mFlags.reset(Flag::HasLinkedRigidBodyWithoutFlag10);
    }
}

void RigidBodyMotionProxy::resetLinkedRigidBody() {
    if (!mLinkedRigidBody)
        return;

    auto lock = mBody->makeScopedLock(mBody->isFlag8Set());
    if (mLinkedRigidBody) {
        mLinkedRigidBody->getMotionAccessorForProxy()->deregisterAccessor(this);
        mLinkedRigidBody = nullptr;
        mFlags.reset(Flag::HasLinkedRigidBodyWithoutFlag10);
    }
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

void RigidBodyMotionProxy::freeze(bool freeze, bool preserve_velocities,
                                  bool preserve_max_impulse) {
    if (!freeze) {
        mBody->setLinearVelocity(mFrozenLinearVelocity);
        mBody->setAngularVelocity(mFrozenAngularVelocity);
        return;
    }

    if (preserve_velocities) {
        mFrozenLinearVelocity = mBody->getLinearVelocity();
        mFrozenAngularVelocity = mBody->getAngularVelocity();
    } else {
        mFrozenLinearVelocity.set(0, 0, 0);
        mFrozenAngularVelocity.set(0, 0, 0);
    }

    mBody->setLinearVelocity(sead::Vector3f::zero);
    mBody->setAngularVelocity(sead::Vector3f::zero);
}

}  // namespace ksys::phys
