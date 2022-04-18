#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include <Havok/Common/Base/Math/SweptTransform/hkSweptTransformfUtil.h>
#include <Havok/Common/Base/Types/Geometry/Aabb/hkAabb.h>
#include <Havok/Physics/Constraint/Data/hkpConstraintData.h>
#include <Havok/Physics2012/Collide/Shape/Compound/Collection/List/hkpListShape.h>
#include <Havok/Physics2012/Collide/Shape/Compound/Tree/Mopp/hkpMoppBvTreeShape.h>
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
#include "KingSystem/Physics/System/physCollisionInfo.h"
#include "KingSystem/Physics/System/physEntityGroupFilter.h"
#include "KingSystem/Physics/System/physGroupFilter.h"
#include "KingSystem/Physics/System/physSensorGroupFilter.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Physics/System/physUserTag.h"
#include "KingSystem/Physics/physConversions.h"
#include "KingSystem/Utils/MathUtil.h"

namespace ksys::phys {

constexpr float MinInertia = 0.001;

RigidBody::RigidBody(Type type, ContactLayerType layer_type, hkpRigidBody* hk_body,
                     const sead::SafeString& name, sead::Heap* heap, bool set_flag_10)
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
    mFlags.change(Flag::_10, set_flag_10);
    mFlags.set(Flag::UseSystemTimeFactor);
}

RigidBody::~RigidBody() {
    if (mType != Type::FromShape && mType != Type::TerrainHeightField &&
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

hkpCollidable* RigidBody::getCollidable() const {
    return getHkBody()->getCollidableRw();
}

// NON_MATCHING: ldr w8, [x20, #0x68] should be ldr w8, [x22] (equivalent)
void RigidBody::addToWorld() {
    // debug code that survived because mFlags is atomic
    static_cast<void>(isAddedToWorld());

    auto lock = makeScopedLock(false);

    if (mMotionAccessor) {
        const bool use_system_time_factor = hasFlag(Flag::UseSystemTimeFactor);
        setTimeFactor(use_system_time_factor ? System::instance()->getTimeFactor() : 1.0f);

        if (isSensor()) {
            auto* accessor = sead::DynamicCast<RigidBodyMotionSensor>(mMotionAccessor);
            if (accessor->hasFlag(RigidBodyMotionSensor::Flag::_400000))
                return;
        }
    }

    if (isRemovingBodyFromWorld()) {
        mMotionFlags.reset(MotionFlag::BodyRemovalRequested);
        mMotionFlags.set(MotionFlag::BodyAddRequested);
    } else if (!isAddingBodyToWorld()) {
        setMotionFlag(MotionFlag::BodyAddRequested);
    }
}

void RigidBody::setMotionFlag(MotionFlag flag) {
    auto lock = sead::makeScopedLock(mCS);

    mMotionFlags.set(flag);

    if (mFlags.isOff(Flag::_20) && mFlags.isOff(Flag::UpdateRequested)) {
        mFlags.set(Flag::UpdateRequested);
        System::instance()->getRigidBodyRequestMgr()->pushRigidBody(getLayerType(), this);
    }
}

bool RigidBody::isActive() const {
    return mHkBody->isActive();
}

bool RigidBody::isAddedToWorld() const {
    return mFlags.isOn(Flag::IsAddedToWorld);
}

bool RigidBody::isAddingBodyToWorld() const {
    return mMotionFlags.isOn(MotionFlag::BodyAddRequested);
}

bool RigidBody::isRemovingBodyFromWorld() const {
    return mMotionFlags.isOn(MotionFlag::BodyRemovalRequested);
}

void RigidBody::removeFromWorld() {
    // debug code that survived because mFlags is atomic?
    static_cast<void>(mFlags.getDirect());

    auto lock = sead::makeScopedLock(mCS);

    if (mMotionFlags.isOn(MotionFlag::BodyAddRequested)) {
        mMotionFlags.reset(MotionFlag::BodyAddRequested);
        mMotionFlags.set(MotionFlag::BodyRemovalRequested);
    } else if (isAddedToWorld()) {
        setMotionFlag(MotionFlag::BodyRemovalRequested);
    }
}

bool RigidBody::removeFromWorldAndResetLinks() {
    // debug code that survived because mFlags is atomic?
    static_cast<void>(mFlags.getDirect());

    auto lock = makeScopedLock(false);

    bool result = true;

    if (isAddedToWorld()) {
        mFlags.reset(Flag::_20);

        if (mMotionFlags.isOn(MotionFlag::BodyAddRequested)) {
            mMotionFlags.reset(MotionFlag::BodyAddRequested);
            mMotionFlags.set(MotionFlag::BodyRemovalRequested);
        }

        setMotionFlag(MotionFlag::BodyRemovalRequested);
        result = false;
    } else if (mFlags.isOn(Flag::UpdateRequested)) {
        System::instance()->getRigidBodyRequestMgr()->pushRigidBody(getLayerType(), this);
        result = false;
    }

    if (isSensor()) {
        auto* accessor = getSensorMotionAccessor();
        if (accessor && accessor->getLinkedRigidBody() != nullptr) {
            mFlags.reset(Flag::_20);
            resetLinkedRigidBody();
            result = false;
        }
    } else if (mMotionAccessor &&
               getEntityMotionAccessor()->hasFlag(RigidBodyMotionEntity::Flag::_2)) {
        mFlags.reset(Flag::_20);
        getEntityMotionAccessor()->deregisterAllAccessors();
        result = false;
    }

    mFlags.set(Flag::_20);
    mFlags.set(Flag::_4);
    return result;
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

void RigidBody::replaceMotionObject() {
    auto* motion = getMotion();
    const hkMotionState motion_state = *motion->getMotionState();
    const auto linvel = mHkBody->getLinearVelocity();
    const auto angvel = mHkBody->getAngularVelocity();
    const auto counter = motion->m_deactivationIntegrateCounter;
    const auto frame0 = motion->m_deactivationNumInactiveFrames[0];
    const auto frame1 = motion->m_deactivationNumInactiveFrames[1];

    if (mMotionFlags.isOn(MotionFlag::Fixed)) {
        const auto position = motion->getPosition();
        const auto rotation = motion->getRotation();
        new (motion) hkpFixedRigidMotion(position, rotation);

        // Restore relevant motion state.
        *motion->getMotionState() = motion_state;
        mHkBody->m_solverData = 0;
        mHkBody->setQualityType(HK_COLLIDABLE_QUALITY_FIXED);

        mMotionFlags.reset(MotionFlag::Fixed);

        motion->m_deactivationIntegrateCounter = counter;
        motion->m_deactivationNumInactiveFrames[0] = frame0;
        motion->m_deactivationNumInactiveFrames[1] = frame1;

        // Freeze the motion state.
        const auto inv_delta = motion_state.getSweptTransform().getInvDeltaTimeSr();
        if (!inv_delta.isEqualZero()) {
            hkSimdReal time;
            if (auto* world = mHkBody->getWorld()) {
                time = world->getCurrentTime();
            } else {
                time = inv_delta.reciprocal() + motion_state.getSweptTransform().getBaseTimeSr();
            }
            hkSweptTransformUtil::freezeMotionState(time, *motion->getMotionState());
        }

    } else if (mMotionFlags.isOn(MotionFlag::Keyframed)) {
        const auto position = motion->getPosition();
        const auto rotation = motion->getRotation();
        new (getMotion()) hkpKeyframedRigidMotion(position, rotation);

        // Restore relevant motion state.
        *motion->getMotionState() = motion_state;
        motion->m_linearVelocity = linvel;
        motion->m_angularVelocity = angvel;
        mHkBody->m_solverData = 0;
        motion->m_deactivationIntegrateCounter = counter;
        motion->m_deactivationNumInactiveFrames[0] = frame0;
        motion->m_deactivationNumInactiveFrames[1] = frame1;
        const bool is_entity = isEntity();
        mHkBody->setQualityType(is_entity && hasFlag(Flag::HighQualityCollidable) ?
                                    HK_COLLIDABLE_QUALITY_MOVING :
                                    HK_COLLIDABLE_QUALITY_KEYFRAMED_REPORTING);
        mMotionFlags.reset(MotionFlag::Keyframed);

    } else if (mMotionFlags.isOn(MotionFlag::Dynamic)) {
        getEntityMotionAccessor()->updateRigidBodyMotionExceptStateAndVel();
        mHkBody->setQualityType(hasFlag(RigidBody::Flag::HighQualityCollidable) ?
                                    HK_COLLIDABLE_QUALITY_BULLET :
                                    HK_COLLIDABLE_QUALITY_DEBRIS_SIMPLE_TOI);
        mMotionFlags.reset(MotionFlag::Dynamic);
    }

    mHkBody->getCollidableRw()->setMotionState(getMotion()->getMotionState());
    // XXX: what the heck?
    mHkBody->getCollidableRw()->setMotionState(getMotion()->getMotionState());

    if (auto* shape = mHkBody->getCollidable()->getShape()) {
        hkVector4 extent_out;
        mHkBody->updateCachedShapeInfo(shape, extent_out);
    }

    if (auto* world = mHkBody->getWorld()) {
        hkpSolverInfo* solver_info = world->getSolverInfo();
        getMotion()->setWorldSelectFlagsNeg(
            solver_info->m_deactivationNumInactiveFramesSelectFlag[0],
            solver_info->m_deactivationNumInactiveFramesSelectFlag[1],
            solver_info->m_deactivationIntegrateCounter);
    }
}

void RigidBody::x_10() {
    auto lock = makeScopedLock();

    if (isEntity()) {
        if (mMotionAccessor &&
            getEntityMotionAccessor()->hasFlag(RigidBodyMotionEntity::Flag::_2)) {
            mFlags.reset(Flag::_20);
            getEntityMotionAccessor()->deregisterAllAccessors();
        }
    } else {  // isSensor()
        auto* accessor = getSensorMotionAccessor();
        if (accessor && accessor->getLinkedRigidBody() != nullptr) {
            mFlags.reset(Flag::_20);
            resetLinkedRigidBody();
        }
    }

    mFlags.set(Flag::_20);
    mFlags.set(Flag::_4);

    removeFromWorldImmediately();
}

void RigidBody::setCollisionInfo(CollisionInfo* info) {
    if (mCollisionInfo != info) {
        if (mCollisionInfo && isAddedToWorld())
            System::instance()->removeRigidBodyFromContactSystem(this);
        mCollisionInfo = info;
    }

    if (isAddedToWorld() && mCollisionInfo && !mCollisionInfo->isLinked())
        System::instance()->registerCollisionInfo(mCollisionInfo);
}

void RigidBody::setContactPointInfo(ContactPointInfo* info) {
    mContactPointInfo = info;
    if (isAddedToWorld() && mContactPointInfo && !mContactPointInfo->isLinked())
        System::instance()->registerContactPointInfo(info);
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
    auto lock = makeScopedLock();

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

static int getLayerBit(int layer, ContactLayerType type) {
    // This is layer for Entity layers and layer - 0x20 for Sensor layers.
    // XXX: this should be using makeContactLayerMask.
    return layer - FirstSensor * int(type);
}

void RigidBody::enableContactLayer(ContactLayer layer) {
    assertLayerType(layer);
    mContactMask.setBit(getLayerBit(layer, getLayerType()));
}

void RigidBody::disableContactLayer(ContactLayer layer) {
    assertLayerType(layer);
    mContactMask.resetBit(getLayerBit(layer, getLayerType()));
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

void RigidBody::enableGroundCollision(bool enabled) {
    if (!isEntity() || isGroundCollisionEnabled() == enabled)
        return;

    if (int(getContactLayer()) == ContactLayer::EntityRagdoll)
        return;

    const auto current_info = getEntityCollisionFilterInfo();
    auto info = current_info;
    info.ground_col_mode =
        enabled ? GroundCollisionMode::Normal : GroundCollisionMode::IgnoreGround;
    if (current_info != info)
        setCollisionFilterInfo(info.raw);
}

bool RigidBody::isGroundCollisionEnabled() const {
    if (!isEntity())
        return false;

    const auto info = getEntityCollisionFilterInfo();

    bool enabled = false;
    enabled |= info.ground_col_mode != GroundCollisionMode::IgnoreGround;
    enabled |= info.unk30;
    return enabled;
}

void RigidBody::enableWaterCollision(bool enabled) {
    if (!isEntity() || isWaterCollisionEnabled() == enabled)
        return;

    if (int(getContactLayer()) == ContactLayer::EntityRagdoll)
        return;

    const auto current_info = getEntityCollisionFilterInfo();
    auto info = current_info;
    info.water_col_mode = enabled ? WaterCollisionMode::Normal : WaterCollisionMode::IgnoreWater;
    if (current_info != info)
        setCollisionFilterInfo(info.raw);
}

bool RigidBody::isWaterCollisionEnabled() const {
    if (!isEntity())
        return false;

    const auto info = getEntityCollisionFilterInfo();

    bool enabled = false;
    // unk30 enables all collisions?
    enabled |= info.unk30;
    enabled |= info.water_col_mode != WaterCollisionMode::IgnoreWater;
    return enabled;
}

ContactLayer RigidBody::getContactLayer() const {
    return getContactLayer(getEntityCollisionFilterInfo());
}

ContactLayer RigidBody::getContactLayer(EntityCollisionMask info) const {
    return isSensor() ? info.getLayerSensor() : info.getLayer();
}

void RigidBody::setContactLayer(ContactLayer layer) {
    if (getLayerType() != getContactLayerType(layer))
        return;

    const auto current_info = getCollisionFilterInfo();
    auto info = current_info;
    if (isSensor())
        info = sensorCollisionMaskSetLayer(layer, info);
    else
        info = makeEntityCollisionMask(layer, info);

    if (current_info != info)
        setCollisionFilterInfo(info);
}

u32 RigidBody::getCollisionFilterInfo() const {
    return mHkBody->getCollisionFilterInfo();
}

static void resetCollisionFilterInfoForListShapes(const hkpShape* shape) {
    while (true) {
        switch (shape->getType()) {
        case hkcdShapeType::LIST: {
            auto* list = static_cast<const hkpListShape*>(shape);
            for (auto k = list->getFirstKey(); k != HK_INVALID_SHAPE_KEY; k = list->getNextKey(k)) {
                // XXX: eww, can we get rid of this const_cast?
                auto* mut_list = const_cast<hkpListShape*>(list);
                mut_list->setCollisionFilterInfo(k, 0xffffffff);
            }
            return;
        }

        case hkcdShapeType::MOPP:
            shape = static_cast<const hkpMoppBvTreeShape*>(shape)->getChild();
            continue;

        default:
            return;
        }
    }
}

void RigidBody::setCollisionFilterInfo(u32 info) {
    const auto current_layer = getContactLayer();

    const auto lock = makeScopedLock();

    if (getCollisionFilterInfo() != info) {
        if (isAddedToWorld()) {
            if (int(current_layer) != getContactLayer(EntityCollisionMask(info)))
                System::instance()->removeRigidBodyFromContactSystem(this);
        }

        mHkBody->setCollisionFilterInfo(info);
        if (auto* shape = mHkBody->getCollidableRw()->getShape())
            resetCollisionFilterInfoForListShapes(shape);

        if (isAddedToWorld())
            setMotionFlag(MotionFlag::_8000);
    }
}

void RigidBody::setSensorReceiverIgnoredLayer(ContactLayer layer) {
    static_cast<void>(isSensor());
    static_cast<void>(isSensor());
    const auto info = sensorCollisionMaskSetIgnoredLayer(true, layer, getCollisionFilterInfo());
    setCollisionFilterInfo(info);
}

void RigidBody::clearSensorReceiverIgnoredLayer() {
    if (!isSensor())
        return;

    if (getContactLayer() == ContactLayer::SensorCustomReceiver)
        return;

    // The layer we pass here is actually irrelevant because we're clearing the layer value anyway.
    const auto info = sensorCollisionMaskSetIgnoredLayer(false, ContactLayer::SensorNoHit,
                                                         getCollisionFilterInfo());

    setCollisionFilterInfo(info);
}

void RigidBody::setContactLayerAndHandler(ContactLayer layer, SystemGroupHandler* handler) {
    setContactLayer(layer);
    setSystemGroupHandler(handler);
}

void RigidBody::setContactLayerAndGroundHit(ContactLayer layer, GroundHit ground_hit) {
    setContactLayer(layer);
    if (isEntity())
        setGroundHitType(ground_hit);
}

void RigidBody::setContactLayerAndGroundHitAndHandler(ContactLayer layer, GroundHit ground_hit,
                                                      SystemGroupHandler* handler) {
    setContactLayer(layer);
    if (isEntity())
        setGroundHitType(ground_hit);
    setSystemGroupHandler(handler);
}

void RigidBody::setSystemGroupHandler(SystemGroupHandler* handler) {
    const auto layer = getContactLayer();
    const auto ground_hit = getGroundHitType();
    const auto info = getCollisionFilterInfo();

    if (handler) {
        if (handler->getLayerType() == getLayerType()) {
            setCollisionFilterInfo(handler->makeCollisionFilterInfo(info, layer, ground_hit));
        } else {
            SEAD_WARN("handler layer type doesn't match rigid body type; ignoring handler");
        }
    } else if (isEntity()) {
        setCollisionFilterInfo(EntityCollisionMask::make(layer, ground_hit).raw);
    } else {
        setCollisionFilterInfo(SensorCollisionMask::make(layer).raw);
    }
}

void RigidBody::setSensorCustomReceiver(const SensorCollisionMask& mask) {
    SensorCollisionMask info = mask;

    if (!isSensor())
        return;

    info.raw = sensorCollisionMaskSetLayer(ContactLayer::SensorCustomReceiver, info.raw);
    setCollisionFilterInfo(info.raw);
}

void RigidBody::setSensorCustomReceiver(const SensorCollisionMask& mask,
                                        const SystemGroupHandler* handler) {
    SensorCollisionMask info = mask;

    if (!isSensor())
        return;

    info.raw = sensorCollisionMaskSetLayer(ContactLayer::SensorCustomReceiver, info.raw);
    if (handler) {
        info.group_handler_index.SetUnsafe(handler->getIndex());
    }
    setCollisionFilterInfo(info.raw);
}

void RigidBody::setGroundHitMask(ContactLayer layer, u32 mask) {
    if (getContactLayerType(layer) == ContactLayerType::Entity)
        setCollisionFilterInfo(makeEntityGroundHitMask(layer, mask));
}

void RigidBody::addGroundTypeToGroundHitMask(GroundHit ground_hit) {
    auto info = getEntityCollisionFilterInfo();

    if (!isEntity() || !info.is_ground_hit_mask)
        return;

    info.ground_hit.addGroundHit(ground_hit);
    setCollisionFilterInfo(info.raw);
}

GroundHit RigidBody::getGroundHitType() const {
    const auto info = getEntityCollisionFilterInfo();
    if (!isEntity())
        return {};
    return info.getGroundHit();
}

void RigidBody::setGroundHitType(GroundHit ground_hit) {
    if (!isEntity())
        return;

    const auto current_info = getCollisionFilterInfo();
    auto info = current_info;
    info = setEntityCollisionMaskGroundHit(ground_hit, info);

    if (current_info != info)
        setCollisionFilterInfo(info);
}

void RigidBody::setColor(const sead::Color4f& color, const void* a, bool b) {
    // Stubbed debug function? This would probably have been used to see Area actors
    // (which are normally invisible).
}

void RigidBody::setPosition(const sead::Vector3f& position, bool propagate_to_linked_motions) {
    if (util::isVectorInvalid(position)) {
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

void RigidBody::setTransform(const sead::Matrix34f& mtx, bool propagate_to_linked_motions) {
    if (util::isMatrixInvalid(mtx)) {
        onInvalidParameter();
        return;
    }

    mMotionAccessor->setTransform(mtx, propagate_to_linked_motions);
}

bool RigidBody::isTransformDirty() const {
    return mMotionFlags.isOn(MotionFlag::DirtyTransform);
}

void RigidBody::updateShape() {
    if (isAddedToWorld()) {
        setMotionFlag(MotionFlag::DirtyShape);
        return;
    }

    auto* shape = getNewHavokShape_();
    if (shape) {
        mHkBody->setShape(shape);
        if (isEntity() && mMotionAccessor)
            mMotionAccessor->increment14();
    } else {
        mHkBody->updateShape();
        if (isEntity() && mMotionAccessor)
            mMotionAccessor->increment10();
    }

    if (mUserTag)
        mUserTag->onBodyShapeChanged(this);
}

void RigidBody::setScale(float scale) {
    if (!hasFlag(Flag::_10))
        return;

    if (scale <= 0.0)
        scale = 1.0;

    if (sead::Mathf::equalsEpsilon(mScale, scale))
        return;

    mScale = updateScale_(scale, mScale);
    updateShape();
}

void RigidBody::changeMotionType(MotionType motion_type) {
    if (getMotionType() == motion_type)
        return;

    if (isAddedToWorld()) {
        switch (motion_type) {
        case MotionType::Dynamic:
            if (isEntity()) {
                setMotionFlag(MotionFlag::Dynamic);
                mMotionFlags.reset(MotionFlag::Fixed);
                mMotionFlags.reset(MotionFlag::Keyframed);
            }
            break;
        case MotionType::Fixed:
            setMotionFlag(MotionFlag::Fixed);
            mMotionFlags.reset(MotionFlag::Dynamic);
            mMotionFlags.reset(MotionFlag::Keyframed);
            break;
        case MotionType::Keyframed:
            setMotionFlag(MotionFlag::Keyframed);
            mMotionFlags.reset(MotionFlag::Dynamic);
            mMotionFlags.reset(MotionFlag::Fixed);
            break;
        case MotionType::Unknown:
        case MotionType::Invalid:
            break;
        }
        return;
    }

    switch (motion_type) {
    case MotionType::Dynamic:
        if (!isEntity())
            return;
        mMotionFlags.set(MotionFlag::Dynamic);
        break;
    case MotionType::Fixed:
        mMotionFlags.set(MotionFlag::Fixed);
        break;
    case MotionType::Keyframed:
        mMotionFlags.set(MotionFlag::Keyframed);
        break;
    case MotionType::Unknown:
    case MotionType::Invalid:
        break;
    }

    doChangeMotionType(motion_type, getMotionType());
    mMotionFlags.set(MotionFlag::DirtyMass);
    mMotionFlags.set(MotionFlag::DirtyInertiaLocal);
    mMotionFlags.set(MotionFlag::DirtyMaxVelOrTimeFactor);
    mMotionFlags.set(MotionFlag::DirtyDampingOrGravityFactor);
    mMotionFlags.set(MotionFlag::DirtyCenterOfMassLocal);
    x_40();
}

void RigidBody::updateMotionTypeRelatedFlags() {
    if (hasFlag(Flag::_20000000) || hasFlag(Flag::_80000000) || hasFlag(Flag::_40000000))
        return;

    switch (getMotionType()) {
    case MotionType::Dynamic:
        mFlags.set(Flag::_80000000);
        mFlags.reset(Flag::_20000000);
        mFlags.reset(Flag::_40000000);
        return;
    case MotionType::Fixed:
        mFlags.set(Flag::_40000000);
        mFlags.reset(Flag::_20000000);
        mFlags.reset(Flag::_80000000);
        return;
    case MotionType::Keyframed:
        mFlags.set(Flag::_20000000);
        mFlags.reset(Flag::_40000000);
        mFlags.reset(Flag::_80000000);
        return;
    case MotionType::Unknown:
    case MotionType::Invalid:
        break;
    }

    mFlags.reset(Flag::_20000000);
    mFlags.reset(Flag::_40000000);
    mFlags.reset(Flag::_80000000);
}

void RigidBody::triggerScheduledMotionTypeChange() {
    if (hasFlag(Flag::_20000000)) {
        changeMotionType(MotionType::Keyframed);
        mFlags.reset(Flag::_20000000);
    } else if (hasFlag(Flag::_40000000)) {
        changeMotionType(MotionType::Fixed);
        mFlags.reset(Flag::_40000000);
    } else if (hasFlag(Flag::_80000000)) {
        changeMotionType(MotionType::Dynamic);
        mFlags.reset(Flag::_80000000);
    }
}

bool RigidBody::setLinearVelocity(const sead::Vector3f& velocity, float epsilon) {
    if (util::isVectorInvalid(velocity)) {
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
    if (util::isVectorInvalid(velocity)) {
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

void RigidBody::changePositionAndRotation(const sead::Matrix34f& transform, float epsilon) {
    const float inv_delta_time = getInvDeltaTime();

    sead::Quatf rotation;
    transform.toQuat(rotation);
    rotation.normalize();

    sead::Vector3f position;
    transform.getTranslation(position);

    const auto hk_position = toHkVec4(position);
    const auto hk_rotation = toHkQuat(rotation);

    hkVector4f linear_velocity, angular_velocity;
    computeLinearVelocity(&linear_velocity, hk_position, hk_rotation, inv_delta_time);
    computeAngularVelocity(&angular_velocity, hk_rotation, inv_delta_time);

    mMotionAccessor->setLinearVelocity(linear_velocity, epsilon);
    mMotionAccessor->setAngularVelocity(angular_velocity, epsilon);
}

void RigidBody::changePosition(const sead::Vector3f& target_position, bool keep_angular_velocity,
                               float epsilon) {
    hkVector4f velocity;
    computeLinearVelocity(&velocity, target_position, keep_angular_velocity);

    mMotionAccessor->setLinearVelocity(velocity, epsilon);

    if (!keep_angular_velocity)
        mMotionAccessor->setAngularVelocity(sead::Vector3f::zero, epsilon);
}

void RigidBody::changeRotation(const sead::Quatf& target_rotation, float epsilon) {
    hkVector4f velocity;
    computeAngularVelocity(&velocity, target_rotation);
    mMotionAccessor->setAngularVelocity(velocity, epsilon);
}

void RigidBody::changeRotation(const sead::Matrix34f& rotation_matrix, float epsilon) {
    hkVector4f velocity;
    sead::Quatf rotation;
    rotation_matrix.toQuat(rotation);
    rotation.normalize();

    computeAngularVelocity(&velocity, rotation);
    mMotionAccessor->setAngularVelocity(velocity, epsilon);
}

void RigidBody::computeAngularVelocity(hkVector4f* velocity, const hkQuaternionf& target_rotation,
                                       float inv_delta_time) const {
    hkQuaternionf hk_current_rot;
    mMotionAccessor->getRotation(&hk_current_rot);

    hkQuaternionf rotation;
    rotation.setMulInverse(target_rotation, hk_current_rot);
    rotation.normalize();

    if (rotation.hasValidAxis()) {
        rotation.getAxis(*velocity);
        velocity->mul(inv_delta_time * rotation.getAngleSr());
    } else {
        velocity->setZero();
    }
}

void RigidBody::computeAngularVelocity(hkVector4f* velocity,
                                       const sead::Quatf& target_rotation) const {
    const float inv_delta_time = getInvDeltaTime();
    const auto hk_target_rot = toHkQuat(target_rotation);
    computeAngularVelocity(velocity, hk_target_rot, inv_delta_time);
}

void RigidBody::computeAngularVelocity(sead::Vector3f* velocity,
                                       const sead::Quatf& target_rotation) const {
    hkVector4f result;
    computeAngularVelocity(&result, target_rotation);
    storeToVec3(velocity, result);
}

void RigidBody::computeAngularVelocity(sead::Vector3f* velocity,
                                       const sead::Matrix34f& rotation_matrix) const {
    sead::Quatf rotation;
    rotation_matrix.toQuat(rotation);
    rotation.normalize();
    computeAngularVelocity(velocity, rotation);
}

void RigidBody::computeLinearVelocity(hkVector4f* velocity, const hkVector4f& target_position,
                                      const hkQuaternionf& rotation, float inv_delta_time) const {
    const auto center_local = toHkVec4(getCenterOfMassInLocal());

    hkVector4f new_center_world;
    new_center_world._setRotatedDir(rotation, center_local);
    new_center_world.add(target_position);

    velocity->setSub(new_center_world, toHkVec4(getCenterOfMassInWorld()));
    velocity->mul(inv_delta_time);
}

KSYS_ALWAYS_INLINE void RigidBody::computeLinearVelocity(hkVector4f* velocity,
                                                         const hkVector4f& target_position,
                                                         bool take_angular_velocity_into_account,
                                                         float inv_delta_time) const {
    auto hk_current_pos = toHkVec4(getPosition());

    if (take_angular_velocity_into_account) {
        const auto center = getCenterOfMassInLocal();
        if (center.x == 0 && center.y == 0 && center.z == 0) {
            hkVector4f rel_pos;
            rel_pos.setSub(hk_current_pos, toHkVec4(getCenterOfMassInWorld()));

            hkVector4f correction;
            correction.setCross(toHkVec4(getAngularVelocity()), rel_pos);
            correction.mul(1.0f / inv_delta_time);
            hk_current_pos.add(correction);
        }
    }

    velocity->setSub(target_position, hk_current_pos);
    velocity->mul(inv_delta_time);
}

KSYS_ALWAYS_INLINE void
RigidBody::computeLinearVelocity(hkVector4f* velocity, const sead::Vector3f& target_position,
                                 bool take_angular_velocity_into_account) const {
    const float inv_delta_time = getInvDeltaTime();
    const auto hk_target_pos = toHkVec4(target_position);
    computeLinearVelocity(velocity, hk_target_pos, take_angular_velocity_into_account,
                          inv_delta_time);
}

void RigidBody::computeLinearVelocity(sead::Vector3f* velocity,
                                      const sead::Vector3f& target_position,
                                      bool take_angular_velocity_into_account) const {
    hkVector4f result;
    computeLinearVelocity(&result, target_position, take_angular_velocity_into_account);
    storeToVec3(velocity, result);
}

void RigidBody::computeVelocities(hkVector4f* linear_velocity, hkVector4f* angular_velocity,
                                  const hkVector4f& position, const hkQuaternionf& rotation,
                                  float inv_delta_time) {
    computeLinearVelocity(linear_velocity, position, rotation, inv_delta_time);
    computeAngularVelocity(angular_velocity, rotation, inv_delta_time);
}

void RigidBody::computeVelocities(hkVector4f* linear_velocity, hkVector4f* angular_velocity,
                                  const hkVector4f& position, const hkQuaternionf& rotation) {
    const float inv_delta_time = getInvDeltaTime();
    computeVelocities(linear_velocity, angular_velocity, position, rotation, inv_delta_time);
}

void RigidBody::computeVelocities(sead::Vector3f* linear_velocity, sead::Vector3f* angular_velocity,
                                  const sead::Matrix34f& transform) {
    const float inv_delta_time = getInvDeltaTime();

    sead::Quatf rotation;
    transform.toQuat(rotation);
    rotation.normalize();

    sead::Vector3f position;
    transform.getTranslation(position);

    const auto hk_position = toHkVec4(position);
    const auto hk_rotation = toHkQuat(rotation);

    hkVector4f hk_linear_velocity;
    hkVector4f hk_angular_velocity;
    computeLinearVelocity(&hk_linear_velocity, hk_position, hk_rotation, inv_delta_time);
    computeAngularVelocity(&hk_angular_velocity, hk_rotation, inv_delta_time);

    storeToVec3(linear_velocity, hk_linear_velocity);
    storeToVec3(angular_velocity, hk_angular_velocity);
}

float RigidBody::getInvDeltaTime() const {
    const float time_factor = getTimeFactor();
    return time_factor == 0 ? 0 : (1.f / (time_factor * System::instance()->get64()));
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
        storeToVec3(center, getMotion()->getCenterOfMassInWorld());
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
    if (System::instance()->isPaused())
        return;

    if (hasFlag(Flag::_400) || hasFlag(Flag::_40))
        return;

    if (util::isVectorInvalid(impulse)) {
        onInvalidParameter();
        return;
    }

    if (isEntity())
        getEntityMotionAccessor()->applyLinearImpulse(impulse);
}

void RigidBody::applyAngularImpulse(const sead::Vector3f& impulse) {
    if (System::instance()->isPaused())
        return;

    if (hasFlag(Flag::_400) || hasFlag(Flag::_40))
        return;

    if (util::isVectorInvalid(impulse)) {
        onInvalidParameter();
        return;
    }

    if (isEntity())
        getEntityMotionAccessor()->applyAngularImpulse(impulse);
}

void RigidBody::applyPointImpulse(const sead::Vector3f& impulse, const sead::Vector3f& point) {
    if (System::instance()->isPaused())
        return;

    if (hasFlag(Flag::_400) || hasFlag(Flag::_40))
        return;

    if (util::isVectorInvalid(impulse)) {
        onInvalidParameter();
        return;
    }

    if (util::isVectorInvalid(point)) {
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

float RigidBody::updateScale_(float scale, float old_scale) {
    return old_scale;
}

float RigidBody::getVolume() {
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

    if (isAddedToWorld())
        setMotionFlag(MotionFlag::_10000);
    else
        updateDeactivation();
}

void RigidBody::clearFlag4000000(bool clear) {
    if (mFlags.isOff(Flag::_4000000) == clear)
        return;

    mFlags.change(Flag::_4000000, !clear);

    if (isAddedToWorld())
        setMotionFlag(MotionFlag::_10000);
    else
        updateDeactivation();
}

void RigidBody::clearFlag8000000(bool clear) {
    if (mFlags.isOff(Flag::_8000000) == clear)
        return;

    mFlags.change(Flag::_8000000, !clear);

    if (isAddedToWorld())
        setMotionFlag(MotionFlag::_10000);
    else
        updateDeactivation();
}

const hkpShape* RigidBody::getNewHavokShape_() {
    return nullptr;
}

void* RigidBody::m11() {
    return nullptr;
}

void RigidBody::onMaxPositionExceeded() {
    // debug logging?
    [[maybe_unused]] sead::Vector3f position = getPosition();
    setPosition(sead::Vector3f::zero, true);
}

const char* RigidBody::getName() {
    return mUserTag ? mUserTag->getName().cstr() : getHkBodyName().cstr();
}

void RigidBody::onImpulse(RigidBody* body_b, float impulse) const {
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
        System::instance()->lockWorld(getLayerType());
    lock();
}

void RigidBody::unlock() {
    mCS.unlock();
}

void RigidBody::unlock(bool also_unlock_world) {
    unlock();
    if (also_unlock_world)
        System::instance()->unlockWorld(getLayerType());
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

void RigidBody::assertLayerType(ContactLayer layer) const {
    const auto type = getContactLayerType(layer);
    const auto expected_type = getLayerType();
    SEAD_ASSERT(type == expected_type);
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
