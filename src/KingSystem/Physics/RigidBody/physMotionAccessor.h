#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>
#include <math/seadQuat.h>
#include <math/seadVector.h>
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

class hkQuaternionf;
class hkVector4f;
class hkpMotion;

namespace ksys::phys {

struct RigidBodyInstanceParam;

class MotionAccessor {
    SEAD_RTTI_BASE(MotionAccessor)
public:
    explicit MotionAccessor(RigidBody* body);

    MotionType getMotionType() const;
    hkpMotion* getRigidBodyMotion() const;
    void setMotionFlag(RigidBody::MotionFlag flag);
    bool hasMotionFlagSet(RigidBody::MotionFlag flag) const;
    bool hasMotionFlagDisabled(RigidBody::MotionFlag flag) const;
    void disableMotionFlag(RigidBody::MotionFlag flag);

    virtual void setTransform(const sead::Matrix34f& mtx, bool propagate_to_linked_motions) = 0;
    virtual void setPosition(const sead::Vector3f& position, bool propagate_to_linked_motions) = 0;
    virtual void getPosition(sead::Vector3f* position) = 0;
    virtual void getRotation(sead::Quatf* rotation) = 0;
    virtual void getTransform(sead::Matrix34f* mtx) = 0;

    virtual void setCenterOfMassInLocal(const sead::Vector3f& center) = 0;
    virtual void getCenterOfMassInLocal(sead::Vector3f* center) = 0;

    virtual bool setLinearVelocity(const sead::Vector3f& velocity, float epsilon) = 0;
    virtual bool setLinearVelocity(const hkVector4f& velocity, float epsilon) = 0;
    virtual void getLinearVelocity(sead::Vector3f* velocity) = 0;
    virtual bool setAngularVelocity(const sead::Vector3f& velocity, float epsilon) = 0;
    virtual bool setAngularVelocity(const hkVector4f& velocity, float epsilon) = 0;
    virtual void getAngularVelocity(sead::Vector3f* velocity) = 0;

    virtual void setMaxLinearVelocity(float max) = 0;
    virtual float getMaxLinearVelocity() = 0;
    virtual void setMaxAngularVelocity(float max) = 0;
    virtual float getMaxAngularVelocity() = 0;

    virtual ~MotionAccessor();

    virtual bool init(const RigidBodyInstanceParam& params, sead::Heap* heap) = 0;
    virtual void getRotation(hkQuaternionf* quat) = 0;
    virtual void setTimeFactor(float factor) = 0;
    virtual float getTimeFactor() = 0;

    virtual void freeze(bool freeze, bool preserve_velocities, bool preserve_max_impulse) = 0;
    virtual void resetFrozenState() = 0;

    RigidBody* getBody() const { return mBody; }
    hkpRigidBody* getHkBody() const { return mBody->getHkBody(); }
    u32 get10() const { return _10; }
    u32 get14() const { return _14; }
    void increment10() { ++_10; }
    void increment14() { ++_14; }

protected:
    RigidBody* mBody = nullptr;
    u32 _10 = 0;
    u32 _14 = 0;
};

}  // namespace ksys::phys
