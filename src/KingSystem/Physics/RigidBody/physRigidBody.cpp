#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include <Havok/Physics2012/Dynamics/Collide/hkpResponseModifier.h>
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Havok/Physics2012/Dynamics/Motion/Rigid/hkpFixedRigidMotion.h>
#include <Havok/Physics2012/Dynamics/Motion/Rigid/hkpKeyframedRigidMotion.h>
#include "KingSystem/Physics/RigidBody/physMotionAccessor.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyMotion.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyMotionProxy.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"
#include "KingSystem/Physics/System/physMemSystem.h"
#include "KingSystem/Physics/physConversions.h"

namespace ksys::phys {

constexpr float MinInertia = 0.001;

RigidBody::RigidBody(Type type, u32 mass_scaling, hkpRigidBody* hk_body,
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
    if (mFlags.isOff(Flag::MassScaling)) {
        mHkBody->m_responseModifierFlags |= hkpResponseModifier::Flags::MASS_SCALING;
    }

    mFlags.change(Flag::IsCharacterController, isCharacterControllerType());
    mFlags.change(Flag::MassScaling, mass_scaling == 1);
    mFlags.change(Flag::_10, a7);
    mFlags.set(Flag::_100);
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
    if (isMassScaling())
        mMotionAccessor = new (heap) RigidBodyMotionProxy(this);
    else
        mMotionAccessor = new (heap) RigidBodyMotion(this);
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

void RigidBody::setMotionFlag(MotionFlag flag) {
    auto lock = sead::makeScopedLock(mCS);

    mMotionFlags.set(flag);

    if (mFlags.isOff(Flag::_20) && mFlags.isOff(Flag::_2)) {
        mFlags.set(Flag::_2);
        MemSystem::instance()->getRigidBodyRequestMgr()->sub_7100FA6C8C(
            mFlags.isOn(Flag::MassScaling), this);
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

MotionType RigidBody::getMotionType() const {
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

hkpMotion* RigidBody::getMotion() const {
    return getHkBody()->getMotion();
}

}  // namespace ksys::phys
