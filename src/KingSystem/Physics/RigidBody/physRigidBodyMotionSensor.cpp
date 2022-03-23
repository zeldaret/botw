#include "KingSystem/Physics/RigidBody/physRigidBodyMotionSensor.h"
#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include "KingSystem/Physics/RigidBody/physRigidBodyMotionEntity.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"
#include "KingSystem/Physics/physConversions.h"

namespace ksys::phys {

RigidBodyMotionSensor::RigidBodyMotionSensor(RigidBody* body) : MotionAccessor(body) {}

RigidBodyMotionSensor::~RigidBodyMotionSensor() {
    resetLinkedRigidBody();
}

bool RigidBodyMotionSensor::init(const RigidBodyInstanceParam& params, sead::Heap* heap) {
    mMaxLinearVelocity = params.max_linear_velocity;
    mMaxAngularVelocity = params.max_angular_velocity_rad;
    mTimeFactor = params.time_factor;
    return true;
}

KSYS_ALWAYS_INLINE void RigidBodyMotionSensor::setTransformImpl(const sead::Matrix34f& mtx) {
    if (mBody->isAddedToWorld()) {
        setMotionFlag(RigidBody::MotionFlag::DirtyTransform);
        return;
    }

    hkTransformf transform;
    toHkTransform(&transform, mtx);
    mBody->getHkBody()->getMotion()->setTransform(transform);
}

void RigidBodyMotionSensor::setTransform(const sead::Matrix34f& mtx,
                                         bool propagate_to_linked_motions) {
    mTransform = mtx;
    setTransformImpl(mtx);
}

void RigidBodyMotionSensor::setPosition(const sead::Vector3f& position,
                                        bool propagate_to_linked_motions) {
    if (hasMotionFlagDisabled(RigidBody::MotionFlag::DirtyTransform)) {
        getTransform(&mTransform);
    }

    mTransform.setTranslation(position);
    setTransformImpl(mTransform);
}

void RigidBodyMotionSensor::setTransformFromLinkedBody(const sead::Matrix34f& mtx) {
    if (mFlags.isOff(Flag::HasExtraTranslateForLinkedRigidBody) &&
        mFlags.isOff(Flag::HasExtraRotateForLinkedRigidBody)) {
        setTransform(mtx, false);
        return;
    }

    sead::Matrix34f new_mtx = mtx;

    sead::Vector3f translate;
    if (mFlags.isOn(Flag::HasExtraTranslateForLinkedRigidBody)) {
        translate.setMul(mtx, mLinkedBodyExtraTranslate);
    } else {
        mtx.getTranslation(translate);
    }

    if (mFlags.isOn(Flag::HasExtraRotateForLinkedRigidBody)) {
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
void RigidBodyMotionSensor::setTransformFromLinkedBody(const hkVector4f& hk_translate,
                                                       const hkQuaternionf& hk_rotate) {
    if (mFlags.isOff(Flag::HasExtraTranslateForLinkedRigidBody) &&
        mFlags.isOff(Flag::HasExtraRotateForLinkedRigidBody)) {
        setTransform(makeRT(hk_rotate, hk_translate), false);
        return;
    }

    sead::Matrix34f mtx = makeRT(hk_rotate, hk_translate);

    sead::Vector3f translate;
    if (mFlags.isOn(Flag::HasExtraTranslateForLinkedRigidBody)) {
        translate.setMul(mtx, mLinkedBodyExtraTranslate);
    } else {
        storeToVec3(&translate, hk_translate);
    }

    if (mFlags.isOn(Flag::HasExtraRotateForLinkedRigidBody)) {
        sead::Quatf quat;
        toQuat(&quat, hk_rotate);
        quat *= mLinkedBodyExtraRotate;
        mtx.fromQuat(quat);
    }

    mtx.setTranslation(translate);
    setTransform(mtx, false);
}

void RigidBodyMotionSensor::getPosition(sead::Vector3f* position) {
    if (hasMotionFlagSet(RigidBody::MotionFlag::DirtyTransform)) {
        mTransform.getTranslation(*position);
    } else {
        storeToVec3(position, getRigidBodyMotion()->getPosition());
    }
}

void RigidBodyMotionSensor::getRotation(sead::Quatf* rotation) {
    if (hasMotionFlagSet(RigidBody::MotionFlag::DirtyTransform)) {
        mTransform.toQuat(*rotation);
    } else {
        toQuat(rotation, getRigidBodyMotion()->getRotation());
    }

    rotation->normalize();
}

void RigidBodyMotionSensor::getTransform(sead::Matrix34f* mtx) {
    if (hasMotionFlagSet(RigidBody::MotionFlag::DirtyTransform)) {
        *mtx = mTransform;
    } else {
        const auto& transform = getRigidBodyMotion()->getTransform();
        setMtxRotation(mtx, transform.getRotation());
        setMtxTranslation(mtx, transform.getTranslation());
    }
}

void RigidBodyMotionSensor::setCenterOfMassInLocal(const sead::Vector3f& center) {
    mCenterOfMassInLocal.e = center.e;

    if (mBody->isAddedToWorld()) {
        setMotionFlag(RigidBody::MotionFlag::DirtyCenterOfMassLocal);
        return;
    }

    mBody->getHkBody()->setCenterOfMassLocal(toHkVec4(center));
}

void RigidBodyMotionSensor::getCenterOfMassInLocal(sead::Vector3f* center) {
    if (hasMotionFlagSet(RigidBody::MotionFlag::DirtyCenterOfMassLocal)) {
        center->e = mCenterOfMassInLocal.e;
    } else {
        storeToVec3(center, getRigidBodyMotion()->getCenterOfMassLocal());
    }
}

bool RigidBodyMotionSensor::setLinearVelocity(const sead::Vector3f& velocity, float epsilon) {
    if (velocity.equals(mLinearVelocity, epsilon))
        return false;

    mLinearVelocity.e = velocity.e;
    setMotionFlag(RigidBody::MotionFlag::DirtyLinearVelocity);
    return true;
}

bool RigidBodyMotionSensor::setLinearVelocity(const hkVector4f& velocity, float epsilon) {
    sead::Vector3f vec;
    storeToVec3(&vec, velocity);
    return setLinearVelocity(vec, epsilon);
}

void RigidBodyMotionSensor::getLinearVelocity(sead::Vector3f* velocity) {
    if (hasMotionFlagSet(RigidBody::MotionFlag::DirtyLinearVelocity)) {
        velocity->e = mLinearVelocity.e;
    } else {
        storeToVec3(velocity, getRigidBodyMotion()->getLinearVelocity());
    }
}

bool RigidBodyMotionSensor::setAngularVelocity(const sead::Vector3f& velocity, float epsilon) {
    if (velocity.equals(mAngularVelocity, sead::Mathf::epsilon()))
        return false;

    mAngularVelocity.e = velocity.e;
    setMotionFlag(RigidBody::MotionFlag::DirtyAngularVelocity);
    return true;
}

bool RigidBodyMotionSensor::setAngularVelocity(const hkVector4f& velocity, float epsilon) {
    sead::Vector3f vec;
    storeToVec3(&vec, velocity);
    return setAngularVelocity(vec, epsilon);
}

void RigidBodyMotionSensor::getAngularVelocity(sead::Vector3f* velocity) {
    if (hasMotionFlagSet(RigidBody::MotionFlag::DirtyAngularVelocity)) {
        velocity->e = mAngularVelocity.e;
    } else {
        storeToVec3(velocity, getRigidBodyMotion()->getAngularVelocity());
    }
}

void RigidBodyMotionSensor::setMaxLinearVelocity(float max) {
    mMaxLinearVelocity = max;
    setMotionFlag(RigidBody::MotionFlag::DirtyMaxVelOrTimeFactor);
}

float RigidBodyMotionSensor::getMaxLinearVelocity() {
    if (hasMotionFlagSet(RigidBody::MotionFlag::DirtyMaxVelOrTimeFactor))
        return mMaxLinearVelocity;

    return getRigidBodyMotion()->getMotionState()->m_maxLinearVelocity;
}

void RigidBodyMotionSensor::setMaxAngularVelocity(float max) {
    mMaxAngularVelocity = max;
    setMotionFlag(RigidBody::MotionFlag::DirtyMaxVelOrTimeFactor);
}

float RigidBodyMotionSensor::getMaxAngularVelocity() {
    if (hasMotionFlagSet(RigidBody::MotionFlag::DirtyMaxVelOrTimeFactor))
        return mMaxAngularVelocity;

    return getRigidBodyMotion()->getMotionState()->m_maxAngularVelocity;
}

void RigidBodyMotionSensor::setLinkedRigidBody(RigidBody* body) {
    auto lock = mBody->makeScopedLock();

    if (mLinkedRigidBody == body)
        return;

    if (mLinkedRigidBody) {
        // If we already have a linked rigid body, unlink it first.
        mLinkedRigidBody->getEntityMotionAccessorForSensor()->deregisterAccessor(this);
        mLinkedRigidBody = nullptr;
    }

    if (body) {
        if (body->isEntity() && mFlags.isOff(Flag::HasLinkedRigidBodyWithoutFlag10)) {
            RigidBodyMotionEntity* accessor = body->getEntityMotionAccessorForSensor();
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

void RigidBodyMotionSensor::resetLinkedRigidBody() {
    if (!mLinkedRigidBody)
        return;

    auto lock = mBody->makeScopedLock();
    if (mLinkedRigidBody) {
        mLinkedRigidBody->getEntityMotionAccessorForSensor()->deregisterAccessor(this);
        mLinkedRigidBody = nullptr;
        mFlags.reset(Flag::HasLinkedRigidBodyWithoutFlag10);
    }
}

RigidBody* RigidBodyMotionSensor::getLinkedRigidBody() const {
    return mLinkedRigidBody;
}

bool RigidBodyMotionSensor::isFlag40000Set() const {
    return mFlags.isOn(Flag::_40000);
}

void RigidBodyMotionSensor::copyMotionFromLinkedRigidBody() {
    auto lock = mBody->makeScopedLock();

    auto* accessor = mLinkedRigidBody->getEntityMotionAccessorForSensor();
    auto* linked_hk_body = mLinkedRigidBody->getHkBody();
    auto* this_hk_body = mBody->getHkBody();

    bool reset_needed = false;
    if (mFlags.isOn(Flag::HasLinkedRigidBodyWithoutFlag10)) {
        if (_14 != accessor->get14()) {
            _14 = accessor->get14();
            this_hk_body->setShape(linked_hk_body->getCollidable()->getShape());
            reset_needed = true;
        }

        if (_10 != accessor->get10()) {
            _10 = accessor->get10();
            this_hk_body->updateShape();
            reset_needed = true;
        }
    }

    if (mFlags.isOff(Flag::_40000)) {
        hkVector4f position;
        if (mFlags.isOn(Flag::HasExtraTranslateForLinkedRigidBody)) {
            position.setTransformedPos(linked_hk_body->getTransform(),
                                       toHkVec4(mLinkedBodyExtraTranslate));
        } else {
            position = linked_hk_body->getPosition();
        }

        hkQuaternionf rotation;
        if (mFlags.isOn(Flag::HasExtraRotateForLinkedRigidBody)) {
            rotation.setMul(linked_hk_body->getRotation(), toHkQuat(mLinkedBodyExtraRotate));
        } else {
            rotation = linked_hk_body->getRotation();
        }

        if (mLinkedRigidBody->getMotionType() != MotionType::Fixed) {
            hkVector4f lin_vel;
            hkVector4f ang_vel;
            mBody->computeVelocities(&lin_vel, &ang_vel, position, rotation);

            hkVector4f zero;
            zero.setZero();

            hkVector4f vel_threshold;
            vel_threshold.setAll(0.01);
            constexpr auto mask = hkVector4fComparison::MASK_XYZ;

            const auto set_velocity = [&](const hkVector4f& velocity, auto get, auto set) {
                // abs(vel) > 0.01?
                hkVector4f abs_vel;
                abs_vel.setAbs(velocity);
                if (!vel_threshold.greaterEqual(abs_vel).allAreSet<mask>()) {
                    this_hk_body->activate();
                    set(velocity);
                } else if (!get().equalZero().template allAreSet<mask>()) {
                    this_hk_body->activate();
                    set(zero);
                }
            };

            set_velocity(
                lin_vel, [&] { return this_hk_body->getLinearVelocity(); },
                [&](const auto& vel) { this_hk_body->setLinearVelocity(vel); });

            set_velocity(
                ang_vel, [&] { return this_hk_body->getAngularVelocity(); },
                [&](const auto& vel) { this_hk_body->setAngularVelocity(vel); });
        }
    }

    if (reset_needed)
        hkpRigidBody::updateBroadphaseAndResetCollisionInformationOfWarpedBody(this_hk_body);
}

void RigidBodyMotionSensor::getRotation(hkQuaternionf* quat) {
    sead::Quatf rotation;
    getRotation(&rotation);
    toHkQuat(quat, rotation);
}

void RigidBodyMotionSensor::setTimeFactor(float factor) {
    mTimeFactor = factor;
    setMotionFlag(RigidBody::MotionFlag::DirtyMaxVelOrTimeFactor);
}

float RigidBodyMotionSensor::getTimeFactor() {
    return mTimeFactor;
}

void RigidBodyMotionSensor::freeze(bool freeze, bool preserve_velocities,
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
