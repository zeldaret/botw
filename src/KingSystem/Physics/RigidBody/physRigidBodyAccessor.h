#pragma once

#include <math/seadMatrix.h>
#include <math/seadQuat.h>
#include <math/seadVector.h>
#include "KingSystem/Physics/physDefines.h"

class hkpRigidBody;

namespace ksys::phys {

class RigidBodyAccessor {
public:
    explicit RigidBodyAccessor(hkpRigidBody* body);
    virtual ~RigidBodyAccessor();

    hkpRigidBody* getBody() const { return mBody; }

    MotionType getMotionType() const;

    void getPosition(sead::Vector3f* pos) const;
    void getRotation(sead::Quatf* rot) const;
    void getTransform(sead::Matrix34f* mtx) const;

    void getLinearVelocity(sead::Vector3f* vel) const;
    void getAngularVelocity(sead::Vector3f* vel) const;

    /// Whether `vel` >= abs(c) for each component c of the linear velocity and angular velocity.
    // XXX: does this function even make sense? We're comparing `vel` against two quantities
    // that have different units!
    bool isVelocityGreaterEqual(float vel) const;

    void getPointVelocity(sead::Vector3f* vel, const sead::Vector3f& point) const;

    float getTimeFactor() const;

    /// Both parameters are allowed to be null.
    void getDeltaCenterOfMass(sead::Vector3f* out_delta_pos, sead::Vector3f* out_delta_angle) const;

private:
    hkpRigidBody* mBody;
};

}  // namespace ksys::phys
