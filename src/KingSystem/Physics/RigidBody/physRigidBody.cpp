#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include <Havok/Common/Base/Types/Geometry/Aabb/hkAabb.h>
#include <Havok/Physics/Constraint/Data/hkpConstraintData.h>
#include <Havok/Physics2012/Dynamics/Collide/hkpResponseModifier.h>
#include <Havok/Physics2012/Dynamics/Constraint/hkpConstraintInstance.h>
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Havok/Physics2012/Dynamics/Inertia/hkpInertiaTensorComputer.h>
#include <Havok/Physics2012/Dynamics/Motion/Rigid/hkpFixedRigidMotion.h>
#include <Havok/Physics2012/Dynamics/Motion/Rigid/hkpKeyframedRigidMotion.h>
#include <cmath>
#include "KingSystem/Physics/RigidBody/physMotionAccessor.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyMotionEntity.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyMotionSensor.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyRequestMgr.h"
#include "KingSystem/Physics/System/physMemSystem.h"
#include "KingSystem/Physics/System/physUserTag.h"
#include "KingSystem/Physics/physConversions.h"

namespace ksys::phys {

constexpr float MinInertia = 0.001;

static bool isVectorInvalid(const sead::Vector3f& vec) {
    for (int i = 0; i < 3; ++i) {
        if (std::isnan(vec.e[i]))
            return true;
    }
    return false;
}

RigidBody::RigidBody(Type type, ContactLayerType layer_type, hkpRigidBody* hk_body,
                     const sead::SafeString& name, sead::Heap* heap, bool a7)
    : mCS(heap), mHkBody(hk_body), mRigidBodyAccessor(hk_body), mType(type) {
    if (!name.isEmpty()) {
        mHkBody->setName(name.cstr());
    }
    mHkBody->setUserData(reinterpret_cast<hkUlong>(this));
    mHkBody->m_motion.m_savedMotion = nullptr;
    mHkBody->m_motion.m_motionState.m_timeFactor.setOne();
    mHkBody->enableDeactivation(true);
    mHkBody->getCollidableRw()->m_allowedPenetrationDepth = 0.1f;
    if (mFlags.isOff(Flag::IsSensor)) {
        mHkBody->m_responseModifierFlags |= hkpResponseModifier::Flags::MASS_SCALING;
    }

    mFlags.change(Flag::HighQualityCollidable, isCharacterControllerType());
    mFlags.change(Flag::IsSensor, layer_type == ContactLayerType::Sensor);
    mFlags.change(Flag::_10, a7);
    mFlags.set(Flag::UseSystemTimeFactor);
}

RigidBody::~RigidBody() {
    if (mType != Type::_0 && mType != Type::TerrainHeightField &&
        mType != Type::CharacterController) {
        mHkBody->setName(nullptr);
        mHkBody->deallocateInternalArrays();
    }

    if (mMotionAccessor) {
        delete mMotionAccessor;
        mMotionAccessor = nullptr;
    }
}

inline void RigidBody::createMotionAccessor(sead::Heap* heap) {
    if (isSensor())
        mMotionAccessor = new (heap) RigidBodyMotionSensor(this);
    else
        mMotionAccessor = new (heap) RigidBodyMotionEntity(this);
}

namespace {
struct RigidBodyDynamicInstanceParam : RigidBodyInstanceParam {};
}  // namespace

bool RigidBody::initMotionAccessorForDynamicMotion(sead::Heap* heap) {
    createMotionAccessor(heap);

    RigidBodyDynamicInstanceParam param;
    auto* body = getHkBody();
    param.motion_type = MotionType::Dynamic;
    param.mass = body->getMass();

    hkMatrix3 inertia;
    body->getInertiaLocal(inertia);
    param.inertia = {sead::Mathf::max(inertia(0, 0), MinInertia),
                     sead::Mathf::max(inertia(1, 1), MinInertia),
                     sead::Mathf::max(inertia(2, 2), MinInertia)};
    param.center_of_mass = toVec3(body->getCenterOfMassLocal());
    param.linear_damping = body->getLinearDamping();
    param.angular_damping = body->getAngularDamping();
    param.gravity_factor = body->getGravityFactor();
    param.time_factor = body->getTimeFactor();
    param.max_linear_velocity = body->getMaxLinearVelocity();
    param.max_angular_velocity_rad = body->getMaxAngularVelocity();

    mMotionAccessor->init(param, heap);
    return true;
}

bool RigidBody::initMotionAccessor(const RigidBodyInstanceParam& param, sead::Heap* heap,
                                   bool init_motion) {
    if (init_motion)
        createMotion(static_cast<hkpMaxSizeMotion*>(getMotion()), param.motion_type, param);

    createMotionAccessor(heap);
    mMotionAccessor->init(param, heap);
    return true;
}

bool RigidBody::createMotion(hkpMaxSizeMotion* motion, MotionType motion_type,
                             const RigidBodyInstanceParam& param) {
    auto position = hkVector4f::zero();
    auto rotation = hkQuaternionf::getIdentity();

    hkVector4f center_of_mass;
    loadFromVec3(&center_of_mass, param.center_of_mass);

    auto velocity = hkVector4f::zero();

    switch (motion_type) {
    case MotionType::Fixed:
        new (motion) hkpFixedRigidMotion(position, rotation);
        break;

    case MotionType::Dynamic: {
        hkMatrix3f inertia_local;
        inertia_local.m_col0.set(sead::Mathf::max(param.inertia.x, MinInertia), 0, 0);
        inertia_local.m_col1.set(0, sead::Mathf::max(param.inertia.y, MinInertia), 0);
        inertia_local.m_col2.set(0, 0, sead::Mathf::max(param.inertia.z, MinInertia));

        hkpRigidBody::createDynamicRigidMotion(
            hkpMotion::MOTION_DYNAMIC, position, rotation, param.mass, inertia_local,
            center_of_mass, param.max_linear_velocity, param.max_angular_velocity_rad, motion);

        motion->getMotionState()->m_maxLinearVelocity = param.max_linear_velocity;
        motion->getMotionState()->m_maxAngularVelocity = param.max_angular_velocity_rad;
        motion->setLinearDamping(param.linear_damping);
        motion->setAngularDamping(param.angular_damping);
        motion->setTimeFactor(param.time_factor);
        motion->setGravityFactor(param.gravity_factor);
        motion->setLinearVelocity(velocity);
        motion->setAngularVelocity(velocity);
        break;
    }

    case MotionType::Keyframed:
        new (motion) hkpKeyframedRigidMotion(position, rotation);
        motion->setCenterOfMassInLocal(center_of_mass);
        motion->getMotionState()->m_maxLinearVelocity = param.max_linear_velocity;
        motion->getMotionState()->m_maxAngularVelocity = param.max_angular_velocity_rad;
        motion->setTimeFactor(param.time_factor);
        motion->setLinearVelocity(velocity);
        motion->setAngularVelocity(velocity);
        break;

    case MotionType::Unknown:
    case MotionType::Invalid:
        break;
    }

    if (mFlags.isOff(Flag::_2000000) && mFlags.isOff(Flag::_4000000) &&
        mFlags.isOff(Flag::_8000000)) {
        mHkBody->enableDeactivation(false);
        mHkBody->enableDeactivation(true);
    }

    return true;
}

sead::SafeString RigidBody::getHkBodyName() const {
    const char* name = mHkBody->getName();
    if (!name)
        return sead::SafeString::cEmptyString;
    return name;
}

// NON_MATCHING: ldr w8, [x20, #0x68] should be ldr w8, [x22] (equivalent)
void RigidBody::x_0() {
    // debug code that survived because mFlags is atomic
    static_cast<void>(isFlag8Set());

    auto lock = makeScopedLock(false);

    if (mMotionAccessor) {
        const bool use_system_time_factor = hasFlag(Flag::UseSystemTimeFactor);
        setTimeFactor(use_system_time_factor ? MemSystem::instance()->getTimeFactor() : 1.0f);

        if (isSensor()) {
            auto* accessor = sead::DynamicCast<RigidBodyMotionSensor>(mMotionAccessor);
            if (accessor->hasFlag(RigidBodyMotionSensor::Flag::_400000))
                return;
        }
    }

    if (isMotionFlag2Set()) {
        mMotionFlags.reset(MotionFlag::_2);
        mMotionFlags.set(MotionFlag::_1);
    } else if (!isMotionFlag1Set()) {
        setMotionFlag(MotionFlag::_1);
    }
}

void RigidBody::setMotionFlag(MotionFlag flag) {
    auto lock = sead::makeScopedLock(mCS);

    mMotionFlags.set(flag);

    if (mFlags.isOff(Flag::_20) && mFlags.isOff(Flag::UpdateRequested)) {
        mFlags.set(Flag::UpdateRequested);
        MemSystem::instance()->getRigidBodyRequestMgr()->pushRigidBody(getLayerType(), this);
    }
}

bool RigidBody::isActive() const {
    return mHkBody->isActive();
}

bool RigidBody::isFlag8Set() const {
    return mFlags.isOn(Flag::_8);
}

bool RigidBody::isMotionFlag1Set() const {
    return mMotionFlags.isOn(MotionFlag::_1);
}

bool RigidBody::isMotionFlag2Set() const {
    return mMotionFlags.isOn(MotionFlag::_2);
}

void RigidBody::sub_7100F8D21C() {
    // debug code that survived because mFlags is atomic?
    static_cast<void>(mFlags.isOn(Flag::_8));

    auto lock = sead::makeScopedLock(mCS);

    if (mMotionFlags.isOn(MotionFlag::_1)) {
        mMotionFlags.reset(MotionFlag::_1);
        mMotionFlags.set(MotionFlag::_2);
    } else if (mFlags.isOn(Flag::_8)) {
        setMotionFlag(MotionFlag::_2);
    }
}

RigidBodyMotionEntity* RigidBody::getEntityMotionAccessor() const {
    return sead::DynamicCast<RigidBodyMotionEntity>(mMotionAccessor);
}

RigidBodyMotionEntity* RigidBody::getEntityMotionAccessorForSensor() const {
    return getEntityMotionAccessor();
}

RigidBodyMotionSensor* RigidBody::getSensorMotionAccessor() const {
    if (!isSensor())
        return nullptr;
    if (!mMotionAccessor)
        return nullptr;
    return sead::DynamicCast<RigidBodyMotionSensor>(mMotionAccessor);
}

RigidBody* RigidBody::getLinkedRigidBody() const {
    auto* accessor = getSensorMotionAccessor();
    if (!accessor)
        return nullptr;
    return accessor->getLinkedRigidBody();
}

void RigidBody::resetLinkedRigidBody() const {
    auto* accessor = getSensorMotionAccessor();
    if (!accessor)
        return;
    accessor->resetLinkedRigidBody();
}

bool RigidBody::setLinkedRigidBody(RigidBody* body) {
    if (!isSensor())
        return false;

    if (body != nullptr && hasFlag(Flag::_20))
        return false;

    if (!mMotionAccessor)
        return false;

    auto* accessor = sead::DynamicCast<RigidBodyMotionSensor>(mMotionAccessor);
    if (!accessor)
        return false;

    accessor->setLinkedRigidBody(body);
    return true;
}

bool RigidBody::isSensorMotionFlag40000Set() const {
    auto* accessor = getSensorMotionAccessor();
    if (!accessor)
        return false;
    return accessor->isFlag40000Set();
}

MotionType RigidBody::getMotionType() const {
    if (mMotionFlags.isOn(MotionFlag::Dynamic))
        return MotionType::Dynamic;
    if (mMotionFlags.isOn(MotionFlag::Keyframed))
        return MotionType::Keyframed;
    if (mMotionFlags.isOn(MotionFlag::Fixed))
        return MotionType::Fixed;
    return mRigidBodyAccessor.getMotionType();
}

void RigidBody::setContactPoints(RigidContactPoints* points) {
    mContactPoints = points;
    if (isFlag8Set() && mContactPoints && !mContactPoints->isLinked())
        MemSystem::instance()->registerContactPoints(points);
}

void RigidBody::freeze(bool should_freeze, bool preserve_velocities, bool preserve_max_impulse) {
    if (hasFlag(Flag::Frozen) == should_freeze) {
        if (should_freeze) {
            setLinearVelocity(sead::Vector3f::zero);
            setAngularVelocity(sead::Vector3f::zero);
        }
        return;
    }

    if (!mMotionAccessor) {
        mFlags.change(Flag::Frozen, should_freeze);
        return;
    }

    if (should_freeze) {
        mMotionAccessor->freeze(true, preserve_velocities, preserve_max_impulse);
        mFlags.set(Flag::Frozen);
    } else {
        mFlags.reset(Flag::Frozen);
        mMotionAccessor->freeze(false, preserve_velocities, preserve_max_impulse);
    }
}

void RigidBody::setFixedAndPreserveImpulse(bool fixed, bool mark_linear_vel_as_dirty) {
    if (hasFlag(Flag::FixedWithImpulsePreserved) != fixed) {
        mFlags.change(Flag::FixedWithImpulsePreserved, fixed);
        if (!fixed && mark_linear_vel_as_dirty) {
            setMotionFlag(MotionFlag::DirtyLinearVelocity);
        }
    }

    freeze(hasFlag(Flag::FixedWithImpulsePreserved) || hasFlag(Flag::Fixed), true, true);
}

void RigidBody::setFixed(bool fixed, bool preserve_velocities) {
    if (hasFlag(Flag::Fixed) != fixed) {
        mFlags.change(Flag::Fixed, fixed);
        if (!fixed) {
            setMotionFlag(MotionFlag::DirtyLinearVelocity);
            setMotionFlag(MotionFlag::_40000);
        }
    }

    freeze(hasFlag(Flag::FixedWithImpulsePreserved) || hasFlag(Flag::Fixed), preserve_velocities,
           false);
}

void RigidBody::resetFrozenState() {
    if (mMotionAccessor)
        mMotionAccessor->resetFrozenState();
}

void RigidBody::updateCollidableQualityType(bool high_quality) {
    auto lock = makeScopedLock(isFlag8Set());

    if (isCharacterControllerType()) {
        setCollidableQualityType(HK_COLLIDABLE_QUALITY_CHARACTER);
        mFlags.set(Flag::HighQualityCollidable);
        return;
    }

    switch (getMotionType()) {
    case MotionType::Dynamic:
        setCollidableQualityType(high_quality ? HK_COLLIDABLE_QUALITY_BULLET :
                                                HK_COLLIDABLE_QUALITY_DEBRIS_SIMPLE_TOI);
        break;
    case MotionType::Fixed:
        setCollidableQualityType(HK_COLLIDABLE_QUALITY_FIXED);
        break;
    case MotionType::Keyframed:
        setCollidableQualityType(isEntity() && high_quality ?
                                     HK_COLLIDABLE_QUALITY_MOVING :
                                     HK_COLLIDABLE_QUALITY_KEYFRAMED_REPORTING);
        break;
    case MotionType::Unknown:
    case MotionType::Invalid:
        break;
    }

    mFlags.change(Flag::HighQualityCollidable, high_quality);
}

void RigidBody::setCollidableQualityType(hkpCollidableQualityType quality) {
    getHkBody()->getCollidableRw()->setQualityType(quality);
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

void RigidBody::setPosition(const sead::Vector3f& position, bool propagate_to_linked_motions) {
    if (isVectorInvalid(position)) {
        onInvalidParameter();
        return;
    }

    mMotionAccessor->setPosition(position, propagate_to_linked_motions);
}

void RigidBody::getPosition(sead::Vector3f* position) const {
    if (mMotionAccessor)
        mMotionAccessor->getPosition(position);
    else
        mRigidBodyAccessor.getPosition(position);
}

sead::Vector3f RigidBody::getPosition() const {
    sead::Vector3f position;
    getPosition(&position);
    return position;
}

void RigidBody::getRotation(sead::Quatf* rotation) const {
    if (mMotionAccessor)
        mMotionAccessor->getRotation(rotation);
    else
        mRigidBodyAccessor.getRotation(rotation);
}

sead::Quatf RigidBody::getRotation() const {
    sead::Quatf rotation;
    getRotation(&rotation);
    return rotation;
}

void RigidBody::getPositionAndRotation(sead::Vector3f* position, sead::Quatf* rotation) const {
    getPosition(position);
    getRotation(rotation);
}

void RigidBody::getTransform(sead::Matrix34f* mtx) const {
    if (mMotionAccessor)
        mMotionAccessor->getTransform(mtx);
    else
        mRigidBodyAccessor.getTransform(mtx);
}

sead::Matrix34f RigidBody::getTransform() const {
    sead::Matrix34f transform;
    getTransform(&transform);
    return transform;
}

bool RigidBody::setLinearVelocity(const sead::Vector3f& velocity, float epsilon) {
    if (isVectorInvalid(velocity)) {
        onInvalidParameter();
        return false;
    }

    if (isEntity() && RigidBodyRequestMgr::Config::isLinearVelocityTooHigh(velocity)) {
        onInvalidParameter(1);
        return false;
    }

    return mMotionAccessor->setLinearVelocity(velocity, epsilon);
}

void RigidBody::getLinearVelocity(sead::Vector3f* velocity) const {
    if (mMotionAccessor)
        mMotionAccessor->getLinearVelocity(velocity);
    else
        mRigidBodyAccessor.getLinearVelocity(velocity);
}

sead::Vector3f RigidBody::getLinearVelocity() const {
    sead::Vector3f v;
    getLinearVelocity(&v);
    return v;
}

bool RigidBody::setAngularVelocity(const sead::Vector3f& velocity, float epsilon) {
    if (isVectorInvalid(velocity)) {
        onInvalidParameter();
        return false;
    }

    return mMotionAccessor->setAngularVelocity(velocity, epsilon);
}

void RigidBody::getAngularVelocity(sead::Vector3f* velocity) const {
    if (mMotionAccessor)
        mMotionAccessor->getAngularVelocity(velocity);
    else
        mRigidBodyAccessor.getAngularVelocity(velocity);
}

sead::Vector3f RigidBody::getAngularVelocity() const {
    sead::Vector3f v;
    getAngularVelocity(&v);
    return v;
}

void RigidBody::getPointVelocity(sead::Vector3f* velocity, const sead::Vector3f& point) const {
    const auto rel_pos = point - getCenterOfMassInWorld();
    velocity->setCross(getAngularVelocity(), rel_pos);
    velocity->add(getLinearVelocity());
}

void RigidBody::setCenterOfMassInLocal(const sead::Vector3f& center) {
    sead::Vector3f current_center;
    mMotionAccessor->getCenterOfMassInLocal(&current_center);
    if (current_center != center)
        mMotionAccessor->setCenterOfMassInLocal(center);
}

void RigidBody::getCenterOfMassInLocal(sead::Vector3f* center) const {
    mMotionAccessor->getCenterOfMassInLocal(center);
}

sead::Vector3f RigidBody::getCenterOfMassInLocal() const {
    sead::Vector3f center;
    getCenterOfMassInLocal(&center);
    return center;
}

void RigidBody::getCenterOfMassInWorld(sead::Vector3f* center) const {
    if (mMotionFlags.isAnyOn({MotionFlag::DirtyCenterOfMassLocal, MotionFlag::DirtyTransform})) {
        sead::Vector3f local_center;
        getCenterOfMassInLocal(&local_center);

        sead::Matrix34f transform;
        getTransform(&transform);

        center->setMul(transform, local_center);
    } else {
        auto hk_center = getMotion()->getCenterOfMassInWorld();
        storeToVec3(center, hk_center);
    }
}

sead::Vector3f RigidBody::getCenterOfMassInWorld() const {
    sead::Vector3f center;
    getCenterOfMassInWorld(&center);
    return center;
}

void RigidBody::setMaxLinearVelocity(float max) {
    if (!sead::Mathf::equalsEpsilon(max, getMaxLinearVelocity()))
        mMotionAccessor->setMaxLinearVelocity(max);
}

float RigidBody::getMaxLinearVelocity() const {
    return mMotionAccessor->getMaxLinearVelocity();
}

void RigidBody::setMaxAngularVelocity(float max) {
    if (!sead::Mathf::equalsEpsilon(max, getMaxAngularVelocity()))
        mMotionAccessor->setMaxAngularVelocity(max);
}

float RigidBody::getMaxAngularVelocity() const {
    return mMotionAccessor->getMaxAngularVelocity();
}

void RigidBody::applyLinearImpulse(const sead::Vector3f& impulse) {
    if (MemSystem::instance()->isPaused())
        return;

    if (hasFlag(Flag::_400) || hasFlag(Flag::_40))
        return;

    if (isVectorInvalid(impulse)) {
        onInvalidParameter();
        return;
    }

    if (isEntity())
        getEntityMotionAccessor()->applyLinearImpulse(impulse);
}

void RigidBody::applyAngularImpulse(const sead::Vector3f& impulse) {
    if (MemSystem::instance()->isPaused())
        return;

    if (hasFlag(Flag::_400) || hasFlag(Flag::_40))
        return;

    if (isVectorInvalid(impulse)) {
        onInvalidParameter();
        return;
    }

    if (isEntity())
        getEntityMotionAccessor()->applyAngularImpulse(impulse);
}

void RigidBody::applyPointImpulse(const sead::Vector3f& impulse, const sead::Vector3f& point) {
    if (MemSystem::instance()->isPaused())
        return;

    if (hasFlag(Flag::_400) || hasFlag(Flag::_40))
        return;

    if (isVectorInvalid(impulse)) {
        onInvalidParameter();
        return;
    }

    if (isVectorInvalid(point)) {
        onInvalidParameter();
        return;
    }

    if (isEntity())
        getEntityMotionAccessor()->applyPointImpulse(impulse, point);
}

void RigidBody::setMass(float mass) {
    if (!isEntity())
        return;
    getEntityMotionAccessor()->setMass(mass);
}

float RigidBody::getMass() const {
    if (!isEntity())
        return 0.0;
    return getEntityMotionAccessor()->getMass();
}

float RigidBody::getMassInv() const {
    if (!isEntity())
        return 0.0;
    return getEntityMotionAccessor()->getMassInv();
}

void RigidBody::setInertiaLocal(const sead::Vector3f& inertia) {
    if (!isEntity())
        return;
    getEntityMotionAccessor()->setInertiaLocal(inertia);
}

void RigidBody::getInertiaLocal(sead::Vector3f* inertia) const {
    if (isEntity()) {
        getEntityMotionAccessor()->getInertiaLocal(inertia);
    } else {
        inertia->set(0, 0, 0);
    }
}

void RigidBody::setLinearDamping(float value) {
    if (!isEntity())
        return;
    getEntityMotionAccessor()->setLinearDamping(value);
}

float RigidBody::getLinearDamping() const {
    if (!isEntity())
        return 0.0;
    return getEntityMotionAccessor()->getLinearDamping();
}

void RigidBody::setAngularDamping(float value) {
    if (!isEntity())
        return;
    getEntityMotionAccessor()->setAngularDamping(value);
}

float RigidBody::getAngularDamping() const {
    if (!isEntity())
        return 0.0;
    return getEntityMotionAccessor()->getAngularDamping();
}

void RigidBody::setGravityFactor(float value) {
    if (!isEntity() || !mMotionAccessor)
        return;
    getEntityMotionAccessor()->setGravityFactor(value);
}

float RigidBody::getGravityFactor() const {
    if (!mMotionAccessor || !isEntity())
        return 1.0;
    return getEntityMotionAccessor()->getGravityFactor();
}

bool RigidBody::setTimeFactor(float value) {
    if (!mMotionAccessor)
        return false;

    const float current_time_factor = getTimeFactor();
    if (sead::Mathf::equalsEpsilon(current_time_factor, value, 0.001))
        return false;

    if (hasFlag(Flag::Frozen))
        return false;

    mMotionAccessor->setTimeFactor(value);

    if (value != 0.0 && current_time_factor != 0.0 && isEntity()) {
        setLinearDamping(getLinearDamping());
        setAngularDamping(getAngularDamping());
    }

    return true;
}

float RigidBody::getTimeFactor() const {
    return mMotionAccessor->getTimeFactor();
}

sead::Vector3f RigidBody::getInertiaLocal() const {
    sead::Vector3f inertia;
    getInertiaLocal(&inertia);
    return inertia;
}

float RigidBody::m12(float x, float y) {
    return y;
}

float RigidBody::m4() {
    return 0.0;
}

void RigidBody::setWaterBuoyancyScale(float scale) {
    if (!isEntity())
        return;
    getEntityMotionAccessor()->setWaterBuoyancyScale(scale);
}

float RigidBody::getWaterBuoyancyScale() const {
    if (!isEntity())
        return 0.0;
    return getEntityMotionAccessor()->getWaterBuoyancyScale();
}

void RigidBody::setWaterFlowEffectiveRate(float rate) {
    if (!isEntity())
        return;
    getEntityMotionAccessor()->setWaterFlowEffectiveRate(rate);
}

float RigidBody::getWaterFlowEffectiveRate() const {
    if (!isEntity())
        return 0.0;
    return getEntityMotionAccessor()->getWaterFlowEffectiveRate();
}

void RigidBody::setMagneMassScalingFactor(float factor) {
    if (!isEntity() || !mMotionAccessor)
        return;
    getEntityMotionAccessor()->setMagneMassScalingFactor(factor);
}

float RigidBody::getMagneMassScalingFactor() const {
    if (!isEntity() || !mMotionAccessor)
        return -1.0;
    return getEntityMotionAccessor()->getMagneMassScalingFactor();
}

void RigidBody::setFrictionScale(float scale) {
    if (!isEntity())
        return;
    getEntityMotionAccessor()->setFrictionScale(scale);
}

float RigidBody::getFrictionScale() const {
    if (!isEntity() || !mMotionAccessor)
        return 1.0;
    return getEntityMotionAccessor()->getFrictionScale();
}

void RigidBody::setRestitutionScale(float scale) {
    if (!isEntity())
        return;
    scale = sead::Mathf::clamp(scale, 0.0, 1.0);
    getEntityMotionAccessor()->setRestitutionScale(scale);
}

float RigidBody::getRestitutionScale() const {
    if (!isEntity() || !mMotionAccessor)
        return 1.0;
    return getEntityMotionAccessor()->getRestitutionScale();
}

float RigidBody::getEffectiveRestitutionScale() const {
    if (hasFlag(Flag::_2000) || hasFlag(Flag::_4000) || hasFlag(Flag::_8000) ||
        hasFlag(Flag::_10000)) {
        return getRestitutionScale() * 0.5f;
    }

    return getRestitutionScale();
}

void RigidBody::setMaxImpulse(float max) {
    if (!isEntity())
        return;
    getEntityMotionAccessor()->setMaxImpulse(max);
}

float RigidBody::getMaxImpulse() const {
    if (!isEntity() || !mMotionAccessor)
        return 1.0;
    return getEntityMotionAccessor()->getMaxImpulse();
}

void RigidBody::clearEntityMotionFlag4(bool clear) {
    if (!isEntity() || !mMotionAccessor)
        return;
    getEntityMotionAccessor()->changeFlag(RigidBodyMotionEntity::Flag::_4, !clear);
}

bool RigidBody::isEntityMotionFlag4Off() const {
    if (!isEntity() || !mMotionAccessor)
        return false;
    return !getEntityMotionAccessor()->hasFlag(RigidBodyMotionEntity::Flag::_4);
}

void RigidBody::setEntityMotionFlag8(bool set) {
    if (!isEntity() || !mMotionAccessor)
        return;
    getEntityMotionAccessor()->changeFlag(RigidBodyMotionEntity::Flag::_8, set);
}

bool RigidBody::isEntityMotionFlag8On() const {
    if (!isEntity() || !mMotionAccessor)
        return false;
    return getEntityMotionAccessor()->hasFlag(RigidBodyMotionEntity::Flag::_8);
}

void RigidBody::clearEntityMotionFlag10(bool clear) {
    if (!isEntity() || !mMotionAccessor)
        return;
    getEntityMotionAccessor()->changeFlag(RigidBodyMotionEntity::Flag::_10, !clear);
}

bool RigidBody::isEntityMotionFlag10Off() const {
    if (!isEntity() || !mMotionAccessor)
        return false;
    return !getEntityMotionAccessor()->hasFlag(RigidBodyMotionEntity::Flag::_10);
}

void RigidBody::clearEntityMotionFlag20(bool clear) {
    if (!isEntity() || !mMotionAccessor)
        return;
    getEntityMotionAccessor()->changeFlag(RigidBodyMotionEntity::Flag::_20, !clear);
}

bool RigidBody::isEntityMotionFlag20Off() const {
    if (!isEntity() || !mMotionAccessor)
        return false;
    return !getEntityMotionAccessor()->hasFlag(RigidBodyMotionEntity::Flag::_20);
}

void RigidBody::setEntityMotionFlag80(bool set) {
    if (!isEntity() || !mMotionAccessor)
        return;
    getEntityMotionAccessor()->changeFlag(RigidBodyMotionEntity::Flag::_80, set);
}

bool RigidBody::isEntityMotionFlag80On() const {
    if (!isEntity() || !mMotionAccessor)
        return false;
    return getEntityMotionAccessor()->hasFlag(RigidBodyMotionEntity::Flag::_80);
}

void RigidBody::setColImpulseScale(float scale) {
    if (!isEntity())
        return;
    scale = sead::Mathf::max(scale, 0.0);
    getEntityMotionAccessor()->setColImpulseScale(scale);
}

float RigidBody::getColImpulseScale() const {
    if (!isEntity() || !mMotionAccessor)
        return 1.0;
    return getEntityMotionAccessor()->getColImpulseScale();
}

bool RigidBody::hasConstraintWithUserData() {
    auto lock = makeScopedLock(true);

    for (int i = 0, n = getHkBody()->getNumConstraints(); i < n; ++i) {
        auto* constraint = getHkBody()->getConstraint(i);
        if (constraint->getData()->getType() != hkpConstraintData::CONSTRAINT_TYPE_CONTACT &&
            constraint->m_userData != 0) {
            return true;
        }
    }

    return false;
}

void RigidBody::setEntityMotionFlag40(bool set) {
    if (!isEntity() || isCharacterControllerType())
        return;
    getEntityMotionAccessor()->changeFlag(RigidBodyMotionEntity::Flag::_40, set);
}

bool RigidBody::isEntityMotionFlag40On() const {
    if (!isEntity() || !mMotionAccessor || isCharacterControllerType())
        return false;
    return getEntityMotionAccessor()->hasFlag(RigidBodyMotionEntity::Flag::_40);
}

void RigidBody::resetInertiaAndCenterOfMass() {
    float volume;
    sead::Vector3f center_of_mass;
    sead::Vector3f inertia;
    computeShapeVolumeMassProperties(&volume, &center_of_mass, &inertia);

    setInertiaLocal(inertia);
    setCenterOfMassInLocal(center_of_mass);
}

void RigidBody::computeShapeVolumeMassProperties(float* volume, sead::Vector3f* center_of_mass,
                                                 sead::Vector3f* inertia_tensor) {
    hkMassProperties properties;
    const auto shape = getHkBody()->getCollidable()->getShape();
    const float mass = getMass();
    hkpInertiaTensorComputer::computeShapeVolumeMassProperties(shape, mass, properties);

    if (volume != nullptr)
        *volume = properties.m_volume;

    if (center_of_mass != nullptr)
        storeToVec3(center_of_mass, properties.m_centerOfMass);

    if (inertia_tensor != nullptr) {
        hkVector4f diagonal{properties.m_inertiaTensor.get<0, 0>(),
                            properties.m_inertiaTensor.get<1, 1>(),
                            properties.m_inertiaTensor.get<2, 2>()};
        storeToVec3(inertia_tensor, diagonal);
    }
}

void RigidBody::clearFlag2000000(bool clear) {
    if (mFlags.isOff(Flag::_2000000) == clear)
        return;

    mFlags.change(Flag::_2000000, !clear);

    if (isFlag8Set())
        setMotionFlag(MotionFlag::_10000);
    else
        updateDeactivation();
}

void RigidBody::clearFlag4000000(bool clear) {
    if (mFlags.isOff(Flag::_4000000) == clear)
        return;

    mFlags.change(Flag::_4000000, !clear);

    if (isFlag8Set())
        setMotionFlag(MotionFlag::_10000);
    else
        updateDeactivation();
}

void RigidBody::clearFlag8000000(bool clear) {
    if (mFlags.isOff(Flag::_8000000) == clear)
        return;

    mFlags.change(Flag::_8000000, !clear);

    if (isFlag8Set())
        setMotionFlag(MotionFlag::_10000);
    else
        updateDeactivation();
}

void* RigidBody::m10() {
    return nullptr;
}

void* RigidBody::m11() {
    return nullptr;
}

void RigidBody::resetPosition() {
    // debug logging?
    [[maybe_unused]] sead::Vector3f position = getPosition();
    setPosition(sead::Vector3f::zero, true);
}

const char* RigidBody::getName() {
    return mUserTag ? mUserTag->getName().cstr() : getHkBodyName().cstr();
}

void RigidBody::logPosition() const {
    sead::Vector3f position;
    getPosition(&position);
    // debug logging?
}

static void convertHkAabb(const hkAabb& hk_aabb, sead::BoundBox3f* aabb) {
    hkVector4f center;
    hk_aabb.getCenter(center);

    hkVector4f extents;
    hk_aabb.getExtents(extents);
    auto half_extents = 0.5f * toVec3(extents);

    aabb->setMin(toVec3(center) - half_extents);
    aabb->setMax(toVec3(center) + half_extents);
}

void RigidBody::getAabbInLocal(sead::BoundBox3f* aabb) const {
    hkAabb hk_aabb;
    getHkBody()->getCollidable()->getShape()->getAabb(hkTransformf::getIdentity(), 0.0, hk_aabb);
    convertHkAabb(hk_aabb, aabb);
}

// NON_MATCHING: paired stores in convertHkAabb that shouldn't be paired
void RigidBody::getAabbInWorld(sead::BoundBox3f* aabb) const {
    hkTransformf hk_transform;
    toHkTransform(&hk_transform, getTransform());
    hkAabb hk_aabb;
    getHkBody()->getCollidable()->getShape()->getAabb(hk_transform, 0.0, hk_aabb);
    convertHkAabb(hk_aabb, aabb);
}

void RigidBody::lock() {
    mCS.lock();
}

void RigidBody::lock(bool also_lock_world) {
    if (also_lock_world)
        MemSystem::instance()->lockWorld(getLayerType());
    lock();
}

void RigidBody::unlock() {
    mCS.unlock();
}

void RigidBody::unlock(bool also_unlock_world) {
    unlock();
    if (also_unlock_world)
        MemSystem::instance()->unlockWorld(getLayerType());
}

hkpMotion* RigidBody::getMotion() const {
    return getHkBody()->getMotion();
}

void RigidBody::setEntityMotionFlag1(bool set) {
    if (!isEntity() || !mMotionAccessor)
        return;
    getEntityMotionAccessor()->changeFlag(RigidBodyMotionEntity::Flag::_1, set);
}

bool RigidBody::isEntityMotionFlag1On() const {
    if (!isEntity() || !mMotionAccessor)
        return false;
    return getEntityMotionAccessor()->hasFlag(RigidBodyMotionEntity::Flag::_1);
}

void RigidBody::setEntityMotionFlag100(bool set) {
    if (!isEntity() || !mMotionAccessor)
        return;
    getEntityMotionAccessor()->changeFlag(RigidBodyMotionEntity::Flag::_100, set);
}

bool RigidBody::isEntityMotionFlag100On() const {
    if (!isEntity() || !mMotionAccessor)
        return false;
    return getEntityMotionAccessor()->hasFlag(RigidBodyMotionEntity::Flag::_100);
}

void RigidBody::setEntityMotionFlag200(bool set) {
    if (!isEntity() || !mMotionAccessor)
        return;
    getEntityMotionAccessor()->changeFlag(RigidBodyMotionEntity::Flag::_200, set);
}

bool RigidBody::isEntityMotionFlag200On() const {
    if (!isEntity() || !mMotionAccessor)
        return false;
    return getEntityMotionAccessor()->hasFlag(RigidBodyMotionEntity::Flag::_200);
}

void RigidBody::onInvalidParameter(int code) {
    sead::Vector3f pos, lin_vel, ang_vel;
    mRigidBodyAccessor.getPosition(&pos);
    mRigidBodyAccessor.getLinearVelocity(&lin_vel);
    mRigidBodyAccessor.getAngularVelocity(&ang_vel);
    // debug prints?
    notifyUserTag(code);
}

void RigidBody::notifyUserTag(int code) {
    if (mUserTag)
        mUserTag->m7(this, code);
}

void RigidBody::updateDeactivation() {
    if (mFlags.isOn(Flag::_2000000) || mFlags.isOn(Flag::_4000000) || mFlags.isOn(Flag::_8000000)) {
        if (getHkBody()->isDeactivationEnabled())
            mHkBody->enableDeactivation(false);
    } else if (!getHkBody()->isDeactivationEnabled()) {
        mHkBody->enableDeactivation(true);
    }
}

}  // namespace ksys::phys
