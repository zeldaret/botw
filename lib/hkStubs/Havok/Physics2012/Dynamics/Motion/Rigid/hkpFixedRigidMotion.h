#pragma once

#include <Havok/Physics2012/Dynamics/Motion/Rigid/hkpKeyframedRigidMotion.h>

class hkpFixedRigidMotion : public hkpKeyframedRigidMotion {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpFixedRigidMotion)
    HK_DECLARE_REFLECTION()

    hkpFixedRigidMotion(const hkVector4& position, const hkQuaternion& rotation);
    explicit hkpFixedRigidMotion(hkFinishLoadedObjectFlag flag) : hkpKeyframedRigidMotion(flag) {}

    virtual void getPositionAndVelocities(hkpMotion* motionOut);

    void setStepPosition(hkReal position, hkReal timestep) override;
    /// Asserts if called. Fixed rigid bodies do not move.
    void setLinearVelocity(const hkVector4& newVel) override;
    /// Asserts if called. Fixed rigid bodies do not move.
    void setAngularVelocity(const hkVector4& newVel) override;
};
