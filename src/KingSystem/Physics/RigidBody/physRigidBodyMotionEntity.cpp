#include "KingSystem/Physics/RigidBody/physRigidBodyMotionEntity.h"
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Havok/Physics2012/Dynamics/Motion/Rigid/hkpBoxMotion.h>
#include <Havok/Physics2012/Dynamics/Motion/Rigid/hkpKeyframedRigidMotion.h>
#include <Havok/Physics2012/Dynamics/Motion/Rigid/hkpSphereMotion.h>
#include <Havok/Physics2012/Dynamics/Motion/hkpMotion.h>
#include <basis/seadTypes.h>
#include <cstring>
#include <prim/seadSafeString.h>
#include <prim/seadScopedLock.h>
#include "KingSystem/Physics/RigidBody/physRigidBodyMotionSensor.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"
#include "KingSystem/Physics/physConversions.h"
#include "KingSystem/Utils/Debug.h"

namespace ksys::phys {

static float sImpulseEpsilon = 1e-05;
static float sMaxImpulse = 1700.0;

RigidBodyMotionEntity::RigidBodyMotionEntity(RigidBody* body) : MotionAccessor(body) {}

RigidBodyMotionEntity::~RigidBodyMotionEntity() {
    if (mMotion) {
        delete[] reinterpret_cast<u8*>(mMotion);
        mMotion = nullptr;
    }
}

bool RigidBodyMotionEntity::init(const RigidBodyInstanceParam& params, sead::Heap* heap) {
    auto* motion_storage = new (heap, alignof(hkpMaxSizeMotion)) u8[sizeof(hkpMaxSizeMotion)];
    mMotion = new (motion_storage) hkpMaxSizeMotion;
    mBody->createMotion(static_cast<hkpMaxSizeMotion*>(mMotion), MotionType::Dynamic, params);
    mMaxImpulse = params.max_impulse;
    mColImpulseScale = params.col_impulse_scale;
    mFrictionScale = params.friction_scale;
    mRestitutionScale = params.restitution_scale;
    mWaterBuoyancyScale = params.water_buoyancy_scale;
    mWaterFlowEffectiveRate = params.water_flow_effective_rate;
    mMagneMassScalingFactor = params.magne_mass_scaling_factor;
    return true;
}

void RigidBodyMotionEntity::setTransform(const sead::Matrix34f& mtx,
                                         bool propagate_to_linked_motions) {
    hkTransformf transform;
    toHkTransform(&transform, mtx);
    mMotion->setTransform(transform);

    if (mBody->isAddedToWorld()) {
        setMotionFlag(RigidBody::MotionFlag::DirtyTransform);
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

void RigidBodyMotionEntity::setPosition(const sead::Vector3f& position,
                                        bool propagate_to_linked_motions) {
    auto* motion = getHkBodyMotionOrLocalMotionIf(RigidBody::MotionFlag::DirtyTransform);
    const auto hk_position = toHkVec4(position);
    const auto& hk_rotate = motion->getRotation();

    mMotion->setPositionAndRotation(hk_position, hk_rotate);

    if (mBody->isAddedToWorld()) {
        setMotionFlag(RigidBody::MotionFlag::DirtyTransform);
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

void RigidBodyMotionEntity::getPosition(sead::Vector3f* position) {
    storeToVec3(position, getPosition());
}

hkVector4f RigidBodyMotionEntity::getPosition() const {
    auto* motion = getHkBodyMotionOrLocalMotionIf(RigidBody::MotionFlag::DirtyTransform);
    return motion->getPosition();
}

void RigidBodyMotionEntity::getRotation(sead::Quatf* rotation) {
    toQuat(rotation, getRotation());
}

hkQuaternionf RigidBodyMotionEntity::getRotation() const {
    auto* motion = getHkBodyMotionOrLocalMotionIf(RigidBody::MotionFlag::DirtyTransform);
    return motion->getRotation();
}

void RigidBodyMotionEntity::getTransform(sead::Matrix34f* mtx) {
    auto* motion = getHkBodyMotionOrLocalMotionIf(RigidBody::MotionFlag::DirtyTransform);
    setMtxRotation(mtx, motion->getTransform().getRotation());
    setMtxTranslation(mtx, motion->getTransform().getTranslation());
}

void RigidBodyMotionEntity::setCenterOfMassInLocal(const sead::Vector3f& center) {
    const auto hk_center = toHkVec4(center);
    mMotion->setCenterOfMassInLocal(hk_center);

    if (mBody->isAddedToWorld())
        setMotionFlag(RigidBody::MotionFlag::DirtyCenterOfMassLocal);
    else
        getHkBody()->setCenterOfMassLocal(hk_center);
}

void RigidBodyMotionEntity::getCenterOfMassInLocal(sead::Vector3f* center) {
    storeToVec3(center, mMotion->getCenterOfMassLocal());
}

bool RigidBodyMotionEntity::setLinearVelocity(const sead::Vector3f& velocity, float epsilon) {
    sead::Vector3f current_vel;
    getLinearVelocity(&current_vel);
    if (current_vel.equals(velocity, epsilon))
        return false;

    mMotion->setLinearVelocity(toHkVec4(velocity));
    setMotionFlag(RigidBody::MotionFlag::DirtyLinearVelocity);
    return true;
}

bool RigidBodyMotionEntity::setLinearVelocity(const hkVector4f& velocity, float epsilon) {
    auto* motion = getHkBodyMotionOrLocalMotionIf(RigidBody::MotionFlag::DirtyLinearVelocity);
    if (velocity.allEqual<3>(motion->getLinearVelocity(), epsilon))
        return false;

    mMotion->setLinearVelocity(velocity);
    setMotionFlag(RigidBody::MotionFlag::DirtyLinearVelocity);
    return true;
}

void RigidBodyMotionEntity::getLinearVelocity(sead::Vector3f* velocity) {
    auto* motion = getHkBodyMotionOrLocalMotionIf(RigidBody::MotionFlag::DirtyLinearVelocity);
    storeToVec3(velocity, motion->getLinearVelocity());
}

bool RigidBodyMotionEntity::setAngularVelocity(const sead::Vector3f& velocity, float epsilon) {
    sead::Vector3f current_vel;
    getAngularVelocity(&current_vel);
    if (current_vel.equals(velocity, epsilon))
        return false;

    mMotion->setAngularVelocity(toHkVec4(velocity));
    setMotionFlag(RigidBody::MotionFlag::DirtyAngularVelocity);
    return true;
}

bool RigidBodyMotionEntity::setAngularVelocity(const hkVector4f& velocity, float epsilon) {
    auto* motion = getHkBodyMotionOrLocalMotionIf(RigidBody::MotionFlag::DirtyAngularVelocity);
    if (velocity.allEqual<3>(motion->getAngularVelocity(), epsilon))
        return false;

    mMotion->setAngularVelocity(velocity);
    setMotionFlag(RigidBody::MotionFlag::DirtyAngularVelocity);
    return true;
}

void RigidBodyMotionEntity::getAngularVelocity(sead::Vector3f* velocity) {
    auto* motion = getHkBodyMotionOrLocalMotionIf(RigidBody::MotionFlag::DirtyAngularVelocity);
    storeToVec3(velocity, motion->getAngularVelocity());
}

void RigidBodyMotionEntity::setMaxLinearVelocity(float max) {
    mMotion->getMotionState()->m_maxLinearVelocity = max;
    setMotionFlag(RigidBody::MotionFlag::DirtyMaxVelOrTimeFactor);
}

float RigidBodyMotionEntity::getMaxLinearVelocity() {
    return mMotion->getMotionState()->m_maxLinearVelocity;
}

void RigidBodyMotionEntity::setMaxAngularVelocity(float max) {
    mMotion->getMotionState()->m_maxAngularVelocity = max;
    setMotionFlag(RigidBody::MotionFlag::DirtyMaxVelOrTimeFactor);
}

float RigidBodyMotionEntity::getMaxAngularVelocity() {
    return mMotion->getMotionState()->m_maxAngularVelocity;
}

bool RigidBodyMotionEntity::applyLinearImpulse(const sead::Vector3f& impulse) {
    if (getMotionType() != MotionType::Dynamic)
        return false;

    if (!mMotion)
        return false;

    if (impulse.equals(sead::Vector3f::zero, sImpulseEpsilon))
        return false;

    if (hasMotionFlagDisabled(RigidBody::MotionFlag::DirtyLinearVelocity)) {
        mMotion->setLinearVelocity(getRigidBodyMotion()->getLinearVelocity());
    }

    mMotion->applyLinearImpulse(toHkVec4(impulse));
    setMotionFlag(RigidBody::MotionFlag::DirtyLinearVelocity);
    return true;
}

bool RigidBodyMotionEntity::applyAngularImpulse(const sead::Vector3f& impulse) {
    if (getMotionType() != MotionType::Dynamic)
        return false;

    if (!mMotion)
        return false;

    if (impulse.equals(sead::Vector3f::zero, sImpulseEpsilon))
        return false;

    if (hasMotionFlagDisabled(RigidBody::MotionFlag::DirtyTransform)) {
        auto& rotation = mMotion->getMotionState()->getSweptTransform().m_rotation1;
        rotation = getRigidBodyMotion()->getRotation();
    }

    if (hasMotionFlagDisabled(RigidBody::MotionFlag::DirtyAngularVelocity)) {
        mMotion->setAngularVelocity(getRigidBodyMotion()->getAngularVelocity());
    }

    mMotion->applyAngularImpulse(toHkVec4(impulse));
    setMotionFlag(RigidBody::MotionFlag::DirtyAngularVelocity);
    return true;
}

bool RigidBodyMotionEntity::applyPointImpulse(const sead::Vector3f& impulse,
                                              const sead::Vector3f& point) {
    if (getMotionType() != MotionType::Dynamic)
        return false;

    if (!mMotion)
        return false;

    if (impulse.equals(sead::Vector3f::zero, sImpulseEpsilon))
        return false;

    if (hasMotionFlagDisabled(RigidBody::MotionFlag::DirtyTransform)) {
        auto* state = mMotion->getMotionState();
        auto* body_state = getRigidBodyMotion()->getMotionState();

        if (hasMotionFlagDisabled(RigidBody::MotionFlag::DirtyCenterOfMassLocal)) {
            state->getSweptTransform().m_centerOfMass1 =
                body_state->getSweptTransform().m_centerOfMass1;
        }

        state->getTransform() = body_state->getTransform();
    }

    if (hasMotionFlagDisabled(RigidBody::MotionFlag::DirtyLinearVelocity)) {
        mMotion->setLinearVelocity(getRigidBodyMotion()->getLinearVelocity());
    }

    if (hasMotionFlagDisabled(RigidBody::MotionFlag::DirtyAngularVelocity)) {
        mMotion->setAngularVelocity(getRigidBodyMotion()->getAngularVelocity());
    }

    mMotion->applyPointImpulse(toHkVec4(impulse), toHkVec4(point));
    setMotionFlag(RigidBody::MotionFlag::DirtyLinearVelocity);
    setMotionFlag(RigidBody::MotionFlag::DirtyAngularVelocity);
    return true;
}

void RigidBodyMotionEntity::setMass(float mass) {
    if (arePropertyChangesBlocked()) {
        mMass = mass;
        return;
    }

    mMotion->setMass(mass);
    if (mBody->isAddedToWorld())
        setMotionFlag(RigidBody::MotionFlag::DirtyMass);
    else if (mBody->getMotionType() == MotionType::Dynamic)
        getHkBody()->getMotion()->setMass(mass);
}

float RigidBodyMotionEntity::getMass() const {
    if (arePropertyChangesBlocked())
        return mMass;

    return mMotion->getMass();
}

float RigidBodyMotionEntity::getMassInv() const {
    if (arePropertyChangesBlocked())
        return 1.0f / mMass;

    return mMotion->getMassInv();
}

static inline float max3(float a, float b, float c) {
    return sead::Mathf::max(c, a > b ? a : b);
}

static inline float min3(float a, float b, float c) {
    return sead::Mathf::min(a < b ? a : b, c);
}

void RigidBodyMotionEntity::setInertiaLocal(const sead::Vector3f& inertia) {
    if (mBody->isCharacterControllerType())
        return;

    if (arePropertyChangesBlocked()) {
        mInertiaLocal = inertia;
        return;
    }

    const float max = max3(inertia.x, inertia.y, inertia.z);
    const float min = min3(inertia.x, inertia.y, inertia.z);
    const float threshold = max * 0.8f;

    bool need_to_recreate_motion = false;
    switch (mMotion->getType()) {
    case hkpMotion::MOTION_BOX_INERTIA:
        need_to_recreate_motion = min > threshold;
        break;
    case hkpMotion::MOTION_SPHERE_INERTIA:
        need_to_recreate_motion = min > threshold;
        // The condition is inverted for spheres.
        need_to_recreate_motion ^= true;
        break;
    default:
        break;
    }

    if (need_to_recreate_motion) {
        const float mass = getMass();
        const auto position = getPosition();
        const auto rotation = getRotation();
        const auto gravity_factor = getGravityFactor();

        // Recreate the Havok motion.
        if (min > threshold) {
            hkpSphereMotion tmp_motion(position, rotation);
            mMotion->getMotionStateAndVelocitiesAndDeactivationType(&tmp_motion);
            new (mMotion) hkpSphereMotion(position, rotation);
            tmp_motion.getMotionStateAndVelocitiesAndDeactivationType(mMotion);
        } else {
            // This little trick lets us copy the motion state and various other state
            // out of the existing Havok motion so we can recreate it safely.
            hkpBoxMotion tmp_motion(position, rotation);
            mMotion->getMotionStateAndVelocitiesAndDeactivationType(&tmp_motion);
            new (mMotion) hkpBoxMotion(position, rotation);
            tmp_motion.getMotionStateAndVelocitiesAndDeactivationType(mMotion);
        }

        // Some properties are not automatically transferred over. Copy them manually.
        mMotion->setGravityFactor(gravity_factor);
        mMotion->setMass(mass);
        if (mBody->isAddedToWorld())
            setMotionFlag(RigidBody::MotionFlag::DirtyMiscState);
        else if (mBody->getMotionType() == MotionType::Dynamic)
            updateRigidBodyMotionExceptState();
    }

    hkMatrix3f hk_inertia;
    hk_inertia.m_col0.set(inertia.x, 0, 0);
    hk_inertia.m_col1.set(0, inertia.y, 0);
    hk_inertia.m_col2.set(0, 0, inertia.z);
    mMotion->setInertiaLocal(hk_inertia);

    if (mBody->isAddedToWorld()) {
        setMotionFlag(RigidBody::MotionFlag::DirtyInertiaLocal);
    } else if (mBody->getMotionType() == MotionType::Dynamic &&
               !mBody->isCharacterControllerType()) {
        hkMatrix3f inertia_inv;
        mMotion->getInertiaInvLocal(inertia_inv);
        getHkBody()->getMotion()->setInertiaInvLocal(inertia_inv);
    }
}

void RigidBodyMotionEntity::getInertiaLocal(sead::Vector3f* inertia) const {
    if (arePropertyChangesBlocked()) {
        inertia->e = mInertiaLocal.e;
        return;
    }

    hkMatrix3f hk_inertia;
    mMotion->getInertiaLocal(hk_inertia);
    inertia->x = hk_inertia.getColumn(0).getX();
    inertia->y = hk_inertia.getColumn(1).getY();
    inertia->z = hk_inertia.getColumn(2).getZ();
}

void RigidBodyMotionEntity::setLinearDamping(float value) {
    if (arePropertyChangesBlocked()) {
        mLinearDamping = value;
        return;
    }

    mMotion->setLinearDamping(value);
    if (mBody->isAddedToWorld())
        setMotionFlag(RigidBody::MotionFlag::DirtyDampingOrGravityFactor);
    else if (mBody->getMotionType() == MotionType::Dynamic)
        getHkBody()->setLinearDamping(getTimeFactor() * value);
}

float RigidBodyMotionEntity::getLinearDamping() const {
    if (arePropertyChangesBlocked())
        return mLinearDamping;

    return mMotion->getLinearDamping();
}

void RigidBodyMotionEntity::setAngularDamping(float value) {
    if (arePropertyChangesBlocked()) {
        mAngularDamping = value;
        return;
    }

    mMotion->setAngularDamping(value);
    if (mBody->isAddedToWorld())
        setMotionFlag(RigidBody::MotionFlag::DirtyDampingOrGravityFactor);
    else if (mBody->getMotionType() == MotionType::Dynamic)
        getHkBody()->setAngularDamping(getTimeFactor() * value);
}

float RigidBodyMotionEntity::getAngularDamping() const {
    if (arePropertyChangesBlocked())
        return mAngularDamping;

    return mMotion->getAngularDamping();
}

void RigidBodyMotionEntity::setGravityFactor(float value) {
    if (arePropertyChangesBlocked()) {
        mGravityFactor = value;
        return;
    }

    mMotion->setGravityFactor(value);
    if (mBody->isAddedToWorld())
        setMotionFlag(RigidBody::MotionFlag::DirtyDampingOrGravityFactor);
    else if (mBody->getMotionType() == MotionType::Dynamic)
        getHkBody()->setGravityFactor(value);
}

float RigidBodyMotionEntity::getGravityFactor() const {
    if (arePropertyChangesBlocked())
        return mGravityFactor;

    return mMotion->getGravityFactor();
}

void RigidBodyMotionEntity::setTimeFactor(float factor) {
    mMotion->setTimeFactor(factor);
    setMotionFlag(RigidBody::MotionFlag::DirtyMaxVelOrTimeFactor);
}

float RigidBodyMotionEntity::getTimeFactor() {
    return mMotion->getTimeFactor();
}

void RigidBodyMotionEntity::getRotation(hkQuaternionf* quat) {
    auto* motion = getHkBodyMotionOrLocalMotionIf(RigidBody::MotionFlag::DirtyTransform);
    *quat = motion->getRotation();
}

void RigidBodyMotionEntity::processUpdateFlags() {
    auto* body = getHkBody();
    auto* body_motion = body->getMotion();

    if (hasMotionFlagSet(RigidBody::MotionFlag::DirtyMass)) {
        body_motion->setMassInv(mMotion->getMassInv());
        disableMotionFlag(RigidBody::MotionFlag::DirtyMass);
    }

    if (hasMotionFlagSet(RigidBody::MotionFlag::DirtyInertiaLocal)) {
        if (!mBody->isCharacterControllerType()) {
            hkMatrix3 inertia;
            mMotion->getInertiaInvLocal(inertia);
            body_motion->setInertiaInvLocal(inertia);
        }
        disableMotionFlag(RigidBody::MotionFlag::DirtyInertiaLocal);
    }

    if (hasMotionFlagSet(RigidBody::MotionFlag::DirtyDampingOrGravityFactor)) {
        if (mBody->hasFlag(RigidBody::Flag::FixedWithImpulsePreserved)) {
            body->setLinearDamping(1.0);
            body->setAngularDamping(1.0);
            body->setGravityFactor(0.0);
        } else {
            body->setLinearDamping(mMotion->getLinearDamping());
            body->setAngularDamping(mMotion->getAngularDamping());
            body->setGravityFactor(mMotion->getGravityFactor());
        }
        disableMotionFlag(RigidBody::MotionFlag::DirtyDampingOrGravityFactor);
    }

    if (hasMotionFlagSet(RigidBody::MotionFlag::DirtyMiscState)) {
        updateRigidBodyMotionExceptState();
        disableMotionFlag(RigidBody::MotionFlag::DirtyMiscState);
    }
}

void RigidBodyMotionEntity::updateRigidBodyMotionExceptState() {
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
        getHkBody()->setQualityType(mBody->hasFlag(RigidBody::Flag::HighQualityCollidable) ?
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

void RigidBodyMotionEntity::updateRigidBodyMotionExceptStateAndVel() {
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
    getHkBody()->setQualityType(mBody->hasFlag(RigidBody::Flag::HighQualityCollidable) ?
                                    HK_COLLIDABLE_QUALITY_BULLET :
                                    HK_COLLIDABLE_QUALITY_DEBRIS);
    getHkBody()->getMotion()->m_deactivationIntegrateCounter = deactivation_counter;
}

bool RigidBodyMotionEntity::registerAccessor(RigidBodyMotionSensor* accessor) {
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

    if (mFlags.isOff(Flag::_2) && mBody->isAddedToWorld())
        setMotionFlag(RigidBody::MotionFlag::_80000);

    return true;
}

bool RigidBodyMotionEntity::deregisterAccessor(RigidBodyMotionSensor* accessor) {
    auto lock = sead::makeScopedLock(mCS);

    const int idx = mLinkedAccessors.indexOf(accessor);
    if (idx < 0)
        return false;

    // Found the accessor -- now we just need to erase it.
    if (mFlags.isOn(Flag::_2) && mBody->isAddedToWorld())
        setMotionFlag(RigidBody::MotionFlag::_80000);
    mLinkedAccessors.erase(idx);
    return true;
}

bool RigidBodyMotionEntity::deregisterAllAccessors() {
    auto lock = sead::makeScopedLock(mCS);

    // For efficiency reasons, deregister starting from the end of the array.
    // Popping from the end is O(1) while erasing from the beginning of a n-sized array
    // would lead to a total complexity of O(n^2).
    for (int i = 0, n = mLinkedAccessors.size(); i < n; ++i) {
        mLinkedAccessors.back()->resetLinkedRigidBody();
    }

    if (mFlags.isOn(Flag::_2) && mBody->isAddedToWorld())
        setMotionFlag(RigidBody::MotionFlag::_80000);
    return true;
}

void RigidBodyMotionEntity::copyTransformToAllLinkedBodies() {
    auto lock = sead::makeScopedLock(mCS);

    for (int i = 0, n = mLinkedAccessors.size(); i < n; ++i) {
        auto* body = mLinkedAccessors[i]->getBody();
        if (!body->isAddedToWorld() && body->isAddingBodyToWorld()) {
            sead::Matrix34f transform;
            mBody->getTransform(&transform);
            body->setTransform(transform, true);
        }
    }
}

void RigidBodyMotionEntity::copyMotionToAllLinkedBodies() {
    auto lock = sead::makeScopedLock(mCS);

    for (int i = 0, n = mLinkedAccessors.size(); i < n; ++i) {
        mLinkedAccessors[i]->copyMotionFromLinkedRigidBody();
    }
}

void RigidBodyMotionEntity::freeze(bool freeze, bool preserve_velocities,
                                   bool preserve_max_impulse) {
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

void RigidBodyMotionEntity::setImpulseEpsilon(float epsilon) {
    sImpulseEpsilon = epsilon;
}

void RigidBodyMotionEntity::setDefaultMaxImpulse(float max_impulse) {
    sMaxImpulse = max_impulse;
}

}  // namespace ksys::phys
