#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include <Havok/Physics2012/Dynamics/Collide/hkpResponseModifier.h>
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Havok/Physics2012/Dynamics/Motion/Rigid/hkpFixedRigidMotion.h>
#include <Havok/Physics2012/Dynamics/Motion/Rigid/hkpKeyframedRigidMotion.h>
#include <cmath>
#include "KingSystem/Physics/RigidBody/physMotionAccessor.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyMotion.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyMotionProxy.h"
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
        MemSystem::instance()->getRigidBodyRequestMgr()->pushRigidBody(
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

RigidBodyMotion* RigidBody::getMotionAccessor() const {
    return sead::DynamicCast<RigidBodyMotion>(mMotionAccessor);
}

RigidBodyMotion* RigidBody::getMotionAccessorForProxy() const {
    return getMotionAccessor();
}

RigidBodyMotionProxy* RigidBody::getMotionProxy() const {
    if (!isMassScaling())
        return nullptr;
    if (!mMotionAccessor)
        return nullptr;
    return sead::DynamicCast<RigidBodyMotionProxy>(mMotionAccessor);
}

RigidBody* RigidBody::getLinkedRigidBody() const {
    auto* proxy = getMotionProxy();
    if (!proxy)
        return nullptr;
    return proxy->getLinkedRigidBody();
}

void RigidBody::resetLinkedRigidBody() const {
    auto* proxy = getMotionProxy();
    if (!proxy)
        return;
    proxy->resetLinkedRigidBody();
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

void RigidBody::resetFrozenState() {
    if (mMotionAccessor)
        mMotionAccessor->resetFrozenState();
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

    if (!isMassScaling() && RigidBodyRequestMgr::Config::isLinearVelocityTooHigh(velocity)) {
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

    if (!isMassScaling())
        getMotionAccessor()->applyLinearImpulse(impulse);
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

    if (!isMassScaling())
        getMotionAccessor()->applyAngularImpulse(impulse);
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

    if (!isMassScaling())
        getMotionAccessor()->applyPointImpulse(impulse, point);
}

void RigidBody::setMass(float mass) {
    if (isMassScaling())
        return;
    getMotionAccessor()->setMass(mass);
}

float RigidBody::getMass() const {
    if (isMassScaling())
        return 0.0;
    return getMotionAccessor()->getMass();
}

float RigidBody::getMassInv() const {
    if (isMassScaling())
        return 0.0;
    return getMotionAccessor()->getMassInv();
}

void RigidBody::lock(bool also_lock_world) {
    if (also_lock_world)
        MemSystem::instance()->lockWorld(getLayerType());
    mCS.lock();
}

void RigidBody::unlock(bool also_unlock_world) {
    mCS.unlock();
    if (also_unlock_world)
        MemSystem::instance()->unlockWorld(getLayerType());
}

hkpMotion* RigidBody::getMotion() const {
    return getHkBody()->getMotion();
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

}  // namespace ksys::phys
