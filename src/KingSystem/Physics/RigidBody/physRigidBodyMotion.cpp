#include "KingSystem/Physics/RigidBody/physRigidBodyMotion.h"
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Havok/Physics2012/Dynamics/Motion/Rigid/hkpKeyframedRigidMotion.h>
#include <Havok/Physics2012/Dynamics/Motion/hkpMotion.h>
#include <basis/seadTypes.h>
#include <cstring>
#include <prim/seadSafeString.h>
#include <prim/seadScopedLock.h>
#include "KingSystem/Physics/RigidBody/physRigidBodyMotionProxy.h"
#include "KingSystem/Physics/physConversions.h"
#include "KingSystem/Utils/Debug.h"

namespace ksys::phys {

static float sImpulseEpsilon = 1e-05;
static float sMaxImpulse = 1700.0;

RigidBodyMotion::RigidBodyMotion(RigidBody* body) : MotionAccessor(body) {}

RigidBodyMotion::~RigidBodyMotion() {
    if (mMotion) {
        delete[] reinterpret_cast<u8*>(mMotion);
        mMotion = nullptr;
    }
}

bool RigidBodyMotion::init(const RigidBodyInstanceParam& params, sead::Heap* heap) {
    auto* motion_storage = new (heap, alignof(hkpMaxSizeMotion)) u8[sizeof(hkpMaxSizeMotion)];
    mMotion = new (motion_storage) hkpMaxSizeMotion;
    mBody->initMotion(mMotion, MotionType::Dynamic, params);
    mMaxImpulse = params.max_impulse;
    mColImpulseScale = params.col_impulse_scale;
    mFrictionScale = params.friction_scale;
    mRestitutionScale = params.restitution_scale;
    mWaterBuoyancyScale = params.water_buoyancy_scale;
    mWaterFlowEffectiveRate = params.water_flow_effective_rate;
    mMagneMassScalingFactor = params.magne_mass_scaling_factor;
    return true;
}

void RigidBodyMotion::setTransform(const sead::Matrix34f& mtx, bool propagate_to_linked_motions) {
    hkTransformf transform;
    toHkTransform(&transform, mtx);
    mMotion->setTransform(transform);

    if (mBody->isFlag8Set()) {
        setMotionFlag(RigidBody::MotionFlag::_20);
    } else {
        getHkBody()->getMotion()->setTransform(transform);
    }

    if (propagate_to_linked_motions) {
        for (int i = 0, n = mLinkedAccessors.size(); i < n; ++i) {
            auto* accessor = mLinkedAccessors[i];
            accessor->setTransformFromLinkedBody(mtx);
            accessor->setLinearVelocity(sead::Vector3f::zero, sead::Mathf::epsilon());
            accessor->setAngularVelocity(sead::Vector3f::zero, sead::Mathf::epsilon());
        }
    }
}

void RigidBodyMotion::setPosition(const sead::Vector3f& position,
                                  bool propagate_to_linked_motions) {
    auto* motion = getMotionDependingOnFlag(RigidBody::MotionFlag::_20);
    const auto hk_position = toHkVec4(position);
    const auto& hk_rotate = motion->getRotation();

    mMotion->setPositionAndRotation(hk_position, hk_rotate);

    if (mBody->isFlag8Set()) {
        setMotionFlag(RigidBody::MotionFlag::_20);
    } else {
        getHkBody()->getMotion()->setPositionAndRotation(hk_position, hk_rotate);
    }

    if (propagate_to_linked_motions) {
        for (int i = 0, n = mLinkedAccessors.size(); i < n; ++i) {
            auto* accessor = mLinkedAccessors[i];
            accessor->setTransformFromLinkedBody(hk_position, hk_rotate);
        }
    }
}

void RigidBodyMotion::getPosition(sead::Vector3f* position) {
    auto* motion = getMotionDependingOnFlag(RigidBody::MotionFlag::_20);
    const auto hk_position = motion->getPosition();
    storeToVec3(position, hk_position);
}

void RigidBodyMotion::getRotation(sead::Quatf* rotation) {
    auto* motion = getMotionDependingOnFlag(RigidBody::MotionFlag::_20);
    toQuat(rotation, motion->getRotation());
}

void RigidBodyMotion::getTransform(sead::Matrix34f* mtx) {
    auto* motion = getMotionDependingOnFlag(RigidBody::MotionFlag::_20);
    setMtxRotation(mtx, motion->getTransform().getRotation());
    setMtxTranslation(mtx, motion->getTransform().getTranslation());
}

void RigidBodyMotion::setCenterOfMassInLocal(const sead::Vector3f& center) {
    const auto hk_center = toHkVec4(center);
    mMotion->setCenterOfMassInLocal(hk_center);

    if (mBody->isFlag8Set())
        setMotionFlag(RigidBody::MotionFlag::_800);
    else
        getHkBody()->setCenterOfMassLocal(hk_center);
}

void RigidBodyMotion::getCenterOfMassInLocal(sead::Vector3f* center) {
    const auto hk_center = mMotion->getCenterOfMassLocal();
    storeToVec3(center, hk_center);
}

bool RigidBodyMotion::setLinearVelocity(const sead::Vector3f& velocity, float epsilon) {
    sead::Vector3f current_vel;
    getLinearVelocity(&current_vel);
    if (current_vel.equals(velocity, epsilon))
        return false;

    mMotion->setLinearVelocity(toHkVec4(velocity));
    setMotionFlag(RigidBody::MotionFlag::_40);
    return true;
}

bool RigidBodyMotion::setLinearVelocity(const hkVector4f& velocity, float epsilon) {
    auto* motion = getMotionDependingOnFlag(RigidBody::MotionFlag::_40);
    if (velocity.allEqual<3>(motion->getLinearVelocity(), epsilon))
        return false;

    mMotion->setLinearVelocity(velocity);
    setMotionFlag(RigidBody::MotionFlag::_40);
    return true;
}

void RigidBodyMotion::getLinearVelocity(sead::Vector3f* velocity) {
    auto* motion = getMotionDependingOnFlag(RigidBody::MotionFlag::_40);
    const auto hk_vel = motion->getLinearVelocity();
    storeToVec3(velocity, hk_vel);
}

bool RigidBodyMotion::setAngularVelocity(const sead::Vector3f& velocity, float epsilon) {
    sead::Vector3f current_vel;
    getAngularVelocity(&current_vel);
    if (current_vel.equals(velocity, epsilon))
        return false;

    mMotion->setAngularVelocity(toHkVec4(velocity));
    setMotionFlag(RigidBody::MotionFlag::_80);
    return true;
}

bool RigidBodyMotion::setAngularVelocity(const hkVector4f& velocity, float epsilon) {
    auto* motion = getMotionDependingOnFlag(RigidBody::MotionFlag::_80);
    if (velocity.allEqual<3>(motion->getAngularVelocity(), epsilon))
        return false;

    mMotion->setAngularVelocity(velocity);
    setMotionFlag(RigidBody::MotionFlag::_80);
    return true;
}

void RigidBodyMotion::getAngularVelocity(sead::Vector3f* velocity) {
    auto* motion = getMotionDependingOnFlag(RigidBody::MotionFlag::_80);
    const auto hk_vel = motion->getAngularVelocity();
    storeToVec3(velocity, hk_vel);
}

void RigidBodyMotion::setMaxLinearVelocity(float max) {
    mMotion->getMotionState()->m_maxLinearVelocity = max;
    setMotionFlag(RigidBody::MotionFlag::_100);
}

float RigidBodyMotion::getMaxLinearVelocity() {
    return mMotion->getMotionState()->m_maxLinearVelocity;
}

void RigidBodyMotion::setMaxAngularVelocity(float max) {
    mMotion->getMotionState()->m_maxAngularVelocity = max;
    setMotionFlag(RigidBody::MotionFlag::_100);
}

float RigidBodyMotion::getMaxAngularVelocity() {
    return mMotion->getMotionState()->m_maxAngularVelocity;
}

bool RigidBodyMotion::applyLinearImpulse(const sead::Vector3f& impulse) {
    if (getMotionType() != MotionType::Dynamic)
        return false;

    if (!mMotion)
        return false;

    if (impulse.equals(sead::Vector3f::zero, sImpulseEpsilon))
        return false;

    if (hasMotionFlagDisabled(RigidBody::MotionFlag::_40)) {
        mMotion->setLinearVelocity(getRigidBodyMotion()->getLinearVelocity());
    }

    mMotion->applyLinearImpulse(toHkVec4(impulse));
    setMotionFlag(RigidBody::MotionFlag::_40);
    return true;
}

bool RigidBodyMotion::applyAngularImpulse(const sead::Vector3f& impulse) {
    if (getMotionType() != MotionType::Dynamic)
        return false;

    if (!mMotion)
        return false;

    if (impulse.equals(sead::Vector3f::zero, sImpulseEpsilon))
        return false;

    if (hasMotionFlagDisabled(RigidBody::MotionFlag::_20)) {
        auto& rotation = mMotion->getMotionState()->getSweptTransform().m_rotation1;
        rotation = getRigidBodyMotion()->getRotation();
    }

    if (hasMotionFlagDisabled(RigidBody::MotionFlag::_80)) {
        mMotion->setAngularVelocity(getRigidBodyMotion()->getAngularVelocity());
    }

    mMotion->applyAngularImpulse(toHkVec4(impulse));
    setMotionFlag(RigidBody::MotionFlag::_80);
    return true;
}

bool RigidBodyMotion::applyPointImpulse(const sead::Vector3f& impulse,
                                        const sead::Vector3f& point) {
    if (getMotionType() != MotionType::Dynamic)
        return false;

    if (!mMotion)
        return false;

    if (impulse.equals(sead::Vector3f::zero, sImpulseEpsilon))
        return false;

    if (hasMotionFlagDisabled(RigidBody::MotionFlag::_20)) {
        auto* state = mMotion->getMotionState();
        auto* body_state = getRigidBodyMotion()->getMotionState();

        if (hasMotionFlagDisabled(RigidBody::MotionFlag::_800)) {
            state->getSweptTransform().m_centerOfMass1 =
                body_state->getSweptTransform().m_centerOfMass1;
        }

        state->getTransform() = body_state->getTransform();
    }

    if (hasMotionFlagDisabled(RigidBody::MotionFlag::_40)) {
        mMotion->setLinearVelocity(getRigidBodyMotion()->getLinearVelocity());
    }

    if (hasMotionFlagDisabled(RigidBody::MotionFlag::_80)) {
        mMotion->setAngularVelocity(getRigidBodyMotion()->getAngularVelocity());
    }

    mMotion->applyPointImpulse(toHkVec4(impulse), toHkVec4(point));
    setMotionFlag(RigidBody::MotionFlag::_40);
    setMotionFlag(RigidBody::MotionFlag::_80);
    return true;
}

void RigidBodyMotion::setMass(float mass) {
    if (bodyHasFlag80000()) {
        mMass = mass;
        return;
    }

    mMotion->setMass(mass);
    if (mBody->isFlag8Set())
        setMotionFlag(RigidBody::MotionFlag::_400);
    else if (mBody->getMotionType() == MotionType::Dynamic)
        getHkBody()->getMotion()->setMass(mass);
}

float RigidBodyMotion::getMass() const {
    if (bodyHasFlag80000())
        return mMass;

    return mMotion->getMass();
}

float RigidBodyMotion::getMassInv() const {
    if (bodyHasFlag80000())
        return 1.0f / mMass;

    return mMotion->getMassInv();
}

void RigidBodyMotion::getInertiaLocal(sead::Vector3f* inertia) const {
    if (bodyHasFlag80000()) {
        inertia->e = mInertiaLocal.e;
        return;
    }

    hkMatrix3f hk_inertia;
    mMotion->getInertiaLocal(hk_inertia);
    inertia->x = hk_inertia.getColumn(0).getX();
    inertia->y = hk_inertia.getColumn(1).getY();
    inertia->z = hk_inertia.getColumn(2).getZ();
}

void RigidBodyMotion::setLinearDamping(float value) {
    if (bodyHasFlag80000()) {
        mLinearDamping = value;
        return;
    }

    mMotion->setLinearDamping(value);
    if (mBody->isFlag8Set())
        setMotionFlag(RigidBody::MotionFlag::_2000);
    else if (mBody->getMotionType() == MotionType::Dynamic)
        getHkBody()->setLinearDamping(getTimeFactor() * value);
}

float RigidBodyMotion::getLinearDamping() const {
    if (bodyHasFlag80000())
        return mLinearDamping;

    return mMotion->getLinearDamping();
}

void RigidBodyMotion::setAngularDamping(float value) {
    if (bodyHasFlag80000()) {
        mAngularDamping = value;
        return;
    }

    mMotion->setAngularDamping(value);
    if (mBody->isFlag8Set())
        setMotionFlag(RigidBody::MotionFlag::_2000);
    else if (mBody->getMotionType() == MotionType::Dynamic)
        getHkBody()->setAngularDamping(getTimeFactor() * value);
}

float RigidBodyMotion::getAngularDamping() const {
    if (bodyHasFlag80000())
        return mAngularDamping;

    return mMotion->getAngularDamping();
}

void RigidBodyMotion::setGravityFactor(float value) {
    if (bodyHasFlag80000()) {
        mGravityFactor = value;
        return;
    }

    mMotion->setGravityFactor(value);
    if (mBody->isFlag8Set())
        setMotionFlag(RigidBody::MotionFlag::_2000);
    else if (mBody->getMotionType() == MotionType::Dynamic)
        getHkBody()->setGravityFactor(value);
}

float RigidBodyMotion::getGravityFactor() const {
    if (bodyHasFlag80000())
        return mGravityFactor;

    return mMotion->getGravityFactor();
}

void RigidBodyMotion::setTimeFactor(float factor) {
    mMotion->setTimeFactor(factor);
    setMotionFlag(RigidBody::MotionFlag::_100);
}

float RigidBodyMotion::getTimeFactor() {
    return mMotion->getTimeFactor();
}

void RigidBodyMotion::getRotation(hkQuaternionf* quat) {
    auto* motion = getMotionDependingOnFlag(RigidBody::MotionFlag::_20);
    *quat = motion->getRotation();
}

void RigidBodyMotion::processUpdateFlags() {
    auto* body = getHkBody();
    auto* body_motion = body->getMotion();

    if (hasMotionFlagSet(RigidBody::MotionFlag::_400)) {
        body_motion->setMassInv(mMotion->getMassInv());
        disableMotionFlag(RigidBody::MotionFlag::_400);
    }

    if (hasMotionFlagSet(RigidBody::MotionFlag::_1000)) {
        if (!mBody->isCharacterControllerType()) {
            hkMatrix3 inertia;
            mMotion->getInertiaInvLocal(inertia);
            body_motion->setInertiaInvLocal(inertia);
        }
        disableMotionFlag(RigidBody::MotionFlag::_1000);
    }

    if (hasMotionFlagSet(RigidBody::MotionFlag::_2000)) {
        if (mBody->hasFlag(RigidBody::Flag::_20000)) {
            body->setLinearDamping(1.0);
            body->setAngularDamping(1.0);
            body->setGravityFactor(0.0);
        } else {
            body->setLinearDamping(mMotion->getLinearDamping());
            body->setAngularDamping(mMotion->getAngularDamping());
            body->setGravityFactor(mMotion->getGravityFactor());
        }
        disableMotionFlag(RigidBody::MotionFlag::_2000);
    }

    if (hasMotionFlagSet(RigidBody::MotionFlag::_200)) {
        updateRigidBodyMotionExceptState();
        disableMotionFlag(RigidBody::MotionFlag::_200);
    }
}

void RigidBodyMotion::updateRigidBodyMotionExceptState() {
    // Copy everything from our hkpMotion to the rigid body's internal motion
    // except the hkMotionState data.
    const hkMotionState state = *getHkBody()->getMotion()->getMotionState();

    // This is technically undefined behaviour because hkpMaxSizeMotion is not trivially
    // copyable and it is also a dynamic class.
    // However, the copy should work fine considering both the destination and the source
    // are hkpMaxSizeMotion objects.
    std::memcpy(static_cast<void*>(getHkBody()->getMotion()), static_cast<const void*>(mMotion),
                sizeof(hkpMaxSizeMotion));

    *getHkBody()->getMotion()->getMotionState() = state;

    // Fix up pointers and invalidate cached info.
    switch (mBody->getMotionType()) {
    case MotionType::Dynamic:
        getHkBody()->setQualityType(mBody->hasFlag(RigidBody::Flag::IsCharacterController) ?
                                        HK_COLLIDABLE_QUALITY_BULLET :
                                        HK_COLLIDABLE_QUALITY_DEBRIS);
        break;
    case MotionType::Fixed:
        getHkBody()->setQualityType(hkpCollidableQualityType::HK_COLLIDABLE_QUALITY_FIXED);
        break;
    case MotionType::Keyframed:
        getHkBody()->setQualityType(
            hkpCollidableQualityType::HK_COLLIDABLE_QUALITY_KEYFRAMED_REPORTING);
        break;
    case MotionType::Unknown:
    case MotionType::Invalid:
        break;
    }

    getHkBody()->getCollidableRw()->setMotionState(getHkBody()->getMotion()->getMotionState());

    hkVector4f extent_out;
    if (auto* shape = getHkBody()->getCollidable()->getShape())
        getHkBody()->updateCachedShapeInfo(shape, extent_out);
}

void RigidBodyMotion::updateRigidBodyMotionExceptStateAndVel() {
    // See updateRigidBodyMotionExceptState() for explanations.
    const hkMotionState state = *getHkBody()->getMotion()->getMotionState();
    const auto linear_vel = getHkBody()->getMotion()->getLinearVelocity();
    const auto angular_vel = getHkBody()->getMotion()->getAngularVelocity();
    const auto deactivation_counter = getHkBody()->getMotion()->m_deactivationIntegrateCounter;

    std::memcpy(static_cast<void*>(getHkBody()->getMotion()), static_cast<const void*>(mMotion),
                sizeof(hkpMaxSizeMotion));

    *getHkBody()->getMotion()->getMotionState() = state;
    getHkBody()->getMotion()->m_linearVelocity = linear_vel;
    getHkBody()->getMotion()->m_angularVelocity = angular_vel;
    getHkBody()->setQualityType(mBody->hasFlag(RigidBody::Flag::IsCharacterController) ?
                                    HK_COLLIDABLE_QUALITY_BULLET :
                                    HK_COLLIDABLE_QUALITY_DEBRIS);
    getHkBody()->getMotion()->m_deactivationIntegrateCounter = deactivation_counter;
}

bool RigidBodyMotion::registerAccessor(RigidBodyMotionProxy* accessor) {
    auto lock = sead::makeScopedLock(mCS);

    if (mLinkedAccessors.isFull()) {
        sead::FixedSafeString<128> list;
        for (int i = 0, n = mLinkedAccessors.size(); i < n; ++i) {
            if (i != 0)
                list.appendWithFormat(", ");
            list.appendWithFormat("%s:%s", mLinkedAccessors[i]->getBody()->getName(),
                                  mLinkedAccessors[i]->getBody()->getHkBodyName().cstr());
        }
        util::PrintDebugFmt("failed to register accessor. existing list: %s", list);
        return false;
    }

    mLinkedAccessors.pushBack(accessor);

    if (mFlags.isOff(Flag::_2) && mBody->isFlag8Set())
        setMotionFlag(RigidBody::MotionFlag::_80000);

    return true;
}

bool RigidBodyMotion::deregisterAccessor(RigidBodyMotionProxy* accessor) {
    auto lock = sead::makeScopedLock(mCS);

    const int idx = mLinkedAccessors.indexOf(accessor);
    if (idx < 0)
        return false;

    // Found the accessor -- now we just need to erase it.
    if (mFlags.isOn(Flag::_2) && mBody->isFlag8Set())
        setMotionFlag(RigidBody::MotionFlag::_80000);
    mLinkedAccessors.erase(idx);
    return true;
}

bool RigidBodyMotion::deregisterAllAccessors() {
    auto lock = sead::makeScopedLock(mCS);

    // For efficiency reasons, deregister starting from the end of the array.
    // Popping from the end is O(1) while erasing from the beginning of a n-sized array
    // would lead to a total complexity of O(n^2).
    for (int i = 0, n = mLinkedAccessors.size(); i < n; ++i) {
        mLinkedAccessors.back()->resetLinkedRigidBody();
    }

    if (mFlags.isOn(Flag::_2) && mBody->isFlag8Set())
        setMotionFlag(RigidBody::MotionFlag::_80000);
    return true;
}

void RigidBodyMotion::copyTransformToAllLinkedBodies() {
    auto lock = sead::makeScopedLock(mCS);

    for (int i = 0, n = mLinkedAccessors.size(); i < n; ++i) {
        auto* body = mLinkedAccessors[i]->getBody();
        if (!body->isFlag8Set() && body->isMotionFlag1Set()) {
            sead::Matrix34f transform;
            mBody->getTransform(&transform);
            body->setTransform(transform, true);
        }
    }
}

void RigidBodyMotion::copyMotionToAllLinkedBodies() {
    auto lock = sead::makeScopedLock(mCS);

    for (int i = 0, n = mLinkedAccessors.size(); i < n; ++i) {
        mLinkedAccessors[i]->copyMotionFromLinkedRigidBody();
    }
}

void RigidBodyMotion::freeze(bool freeze, bool preserve_velocities, bool preserve_max_impulse) {
    if (!freeze) {
        setLinearVelocity(mLinearVelocity, sead::Mathf::epsilon());
        setAngularVelocity(mAngularVelocity, sead::Mathf::epsilon());
        mBody->setLinearDamping(mLinearDamping);
        mBody->setAngularDamping(mAngularDamping);
        mBody->setInertiaLocal(mInertiaLocal);
        mBody->setMass(mMass);
        mBody->setGravityFactor(mGravityFactor);
        mMaxImpulse = mMaxImpulseCopy;
        return;
    }

    const float mass_factor = mFlags.isOn(Flag::_200) ? 20.0 : 1000.0;

    if (preserve_velocities) {
        mLinearVelocity = mBody->getLinearVelocity();
        mAngularVelocity = mBody->getAngularVelocity();
    } else {
        mLinearVelocity.set(0, 0, 0);
        mAngularVelocity.set(0, 0, 0);
    }

    mLinearDamping = mBody->getLinearDamping();
    mAngularDamping = mBody->getAngularDamping();
    mInertiaLocal = mBody->getInertiaLocal();
    mMass = mBody->getMass();
    mGravityFactor = mBody->getGravityFactor();
    mMaxImpulseCopy = mMaxImpulse;

    mBody->setLinearVelocity(sead::Vector3f::zero);
    mBody->setLinearDamping(1.0);
    mBody->setAngularVelocity(sead::Vector3f::zero);
    mBody->setAngularDamping(1.0);

    mBody->setInertiaLocal(mInertiaLocal * mass_factor);
    mBody->setMass(mMass * mass_factor);
    mBody->setGravityFactor(0.0);

    if (!preserve_max_impulse)
        mMaxImpulse = sMaxImpulse;
}

void RigidBodyMotion::setImpulseEpsilon(float epsilon) {
    sImpulseEpsilon = epsilon;
}

void RigidBodyMotion::setMaxImpulse(float max_impulse) {
    sMaxImpulse = max_impulse;
}

}  // namespace ksys::phys
