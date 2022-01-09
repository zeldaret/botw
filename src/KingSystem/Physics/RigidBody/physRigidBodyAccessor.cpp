#include "KingSystem/Physics/RigidBody/physRigidBodyAccessor.h"
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include "KingSystem/Physics/physConversions.h"

namespace ksys::phys {

RigidBodyAccessor::RigidBodyAccessor(hkpRigidBody* body) : mBody(body) {}

RigidBodyAccessor::~RigidBodyAccessor() = default;

MotionType RigidBodyAccessor::getMotionType() const {
    switch (getBody()->getMotionType()) {
    case hkpMotion::MOTION_INVALID:
        break;
    case hkpMotion::MOTION_DYNAMIC:
    case hkpMotion::MOTION_SPHERE_INERTIA:
    case hkpMotion::MOTION_BOX_INERTIA:
        return MotionType::Dynamic;
    case hkpMotion::MOTION_KEYFRAMED:
        return MotionType::Keyframed;
    case hkpMotion::MOTION_FIXED:
        return MotionType::Fixed;
    case hkpMotion::MOTION_THIN_BOX_INERTIA:
        break;
    case hkpMotion::MOTION_CHARACTER:
        return MotionType::Dynamic;
    case hkpMotion::MOTION_MAX_ID:
        break;
    }
    return MotionType::Invalid;
}

void RigidBodyAccessor::getPosition(sead::Vector3f* pos) const {
    toVec3(pos, getBody()->getPosition());
}

void RigidBodyAccessor::getRotation(sead::Quatf* rot) const {
    toQuat(rot, getBody()->getRotation());
}

void RigidBodyAccessor::getTransform(sead::Matrix34f* mtx) const {
    toMtx34(mtx, getBody()->getTransform());
}

void RigidBodyAccessor::getLinearVelocity(sead::Vector3f* vel) const {
    toVec3(vel, getBody()->getLinearVelocity());
}

void RigidBodyAccessor::getAngularVelocity(sead::Vector3f* vel) const {
    toVec3(vel, getBody()->getAngularVelocity());
}

bool RigidBodyAccessor::isVelocityGreaterEqual(float vel) const {
    hkVector4f v;
    v.setAll(vel);

    hkVector4f linvel;
    linvel.setAbs(getBody()->getLinearVelocity());

    hkVector4f angvel;
    angvel.setAbs(getBody()->getAngularVelocity());

    return v.greaterEqual(linvel).allAreSet<hkVector4fComparison::MASK_XYZ>() &&
           v.greaterEqual(angvel).allAreSet<hkVector4fComparison::MASK_XYZ>();
}

void RigidBodyAccessor::getPointVelocity(sead::Vector3f* vel, const sead::Vector3f& point) const {
    const auto p = toHkVec4(point);
    hkVector4f out;
    getBody()->getPointVelocity(p, out);
    toVec3(vel, out);
}

float RigidBodyAccessor::getTimeFactor() const {
    return getBody()->getTimeFactor();
}

void RigidBodyAccessor::getDeltaCenterOfMass(sead::Vector3f* out_delta_pos,
                                             sead::Vector3f* out_delta_angle) const {
    const hkMotionState* state = getBody()->getMotion()->getMotionState();
    const auto center1 = state->getSweptTransform().m_centerOfMass1;
    const auto center0 = state->getSweptTransform().m_centerOfMass0;
    const auto delta_angle = state->m_deltaAngle;

    if (out_delta_pos != nullptr) {
        hkVector4f value;
        value.setSub(center1, center0);
        value.mul(center1.getW());  // W is the time step
        value.store<3>(out_delta_pos->e.data());
    }

    if (out_delta_angle != nullptr) {
        hkVector4f value;
        value.setMul(delta_angle, center1.getW());
        value.store<3>(out_delta_angle->e.data());
    }
}

}  // namespace ksys::phys
