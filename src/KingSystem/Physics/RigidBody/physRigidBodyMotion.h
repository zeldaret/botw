#pragma once

#include "KingSystem/Physics/RigidBody/physMotionAccessor.h"

namespace ksys::phys {

class RigidBodyMotion : public MotionAccessor {
    SEAD_RTTI_OVERRIDE(RigidBodyMotion, MotionAccessor)
public:
    explicit RigidBodyMotion(RigidBody* body);

    bool applyLinearImpulse(const sead::Vector3f& impulse);
    bool applyAngularImpulse(const sead::Vector3f& impulse);
    bool applyPointImpulse(const sead::Vector3f& impulse, const sead::Vector3f& point);

    void setMass(float mass);
};

}  // namespace ksys::phys
