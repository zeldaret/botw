#pragma once

#include <Havok/Common/Base/Types/Physics/MotionState/hkMotionState.h>
#include <Havok/Common/Base/hkBase.h>

class hkpMaxSizeMotion;

class hkpMotion : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpMotion)
    HK_DECLARE_REFLECTION()

    enum MotionType {
        MOTION_INVALID,
        MOTION_DYNAMIC,
        MOTION_SPHERE_INERTIA,
        MOTION_BOX_INERTIA,
        MOTION_KEYFRAMED,
        MOTION_FIXED,
        MOTION_THIN_BOX_INERTIA,
        MOTION_CHARACTER,
        MOTION_MAX_ID
    };

    enum { NUM_INACTIVE_FRAMES_TO_DEACTIVATE = 5 };

    hkpMotion();
    hkpMotion(const hkVector4& position, const hkQuaternion& rotation,
              bool wantDeactivation = false);
    explicit hkpMotion(hkFinishLoadedObjectFlag flag) : hkReferencedObject(flag) {
        if (flag.m_finishing) {
            m_gravityFactor.setOne();
        }
    }

    inline MotionType getType() const { return m_type; }

    virtual void setMass(hkReal m);
    virtual void setMass(hkSimdRealParameter m);

    virtual void setMassInv(hkReal mInv);
    virtual void setMassInv(hkSimdRealParameter mInv);

    virtual void getInertiaLocal(hkMatrix3& inertiaOut) const = 0;
    virtual void getInertiaWorld(hkMatrix3& inertiaOut) const = 0;
    virtual void setInertiaLocal(const hkMatrix3& inertia) = 0;
    virtual void setInertiaInvLocal(const hkMatrix3& inertiaInv) = 0;
    virtual void getInertiaInvLocal(hkMatrix3& inertiaInvOut) const = 0;
    virtual void getInertiaInvWorld(hkMatrix3& inertiaInvOut) const = 0;
    virtual void setCenterOfMassInLocal(const hkVector4& centerOfMass);

    virtual void setPosition(const hkVector4& position);

    virtual void setRotation(const hkQuaternion& rotation);

    virtual void setPositionAndRotation(const hkVector4& position, const hkQuaternion& rotation);

    virtual void setTransform(const hkTransform& transform);

    virtual void setLinearVelocity(const hkVector4& newVel);
    virtual void setAngularVelocity(const hkVector4& newVel);
    virtual void getProjectedPointVelocity(const hkVector4& p, const hkVector4& normal,
                                           hkReal& velOut, hkReal& invVirtMassOut) const = 0;
    virtual void getProjectedPointVelocitySimd(const hkVector4& p, const hkVector4& normal,
                                               hkSimdReal& velOut,
                                               hkSimdReal& invVirtMassOut) const = 0;

    virtual void applyLinearImpulse(const hkVector4& imp);
    virtual void applyPointImpulse(const hkVector4& imp, const hkVector4& p) = 0;
    virtual void applyAngularImpulse(const hkVector4& imp) = 0;

    virtual void applyForce(hkReal deltaTime, const hkVector4& force) = 0;
    virtual void applyForce(hkReal deltaTime, const hkVector4& force, const hkVector4& p) = 0;
    virtual void applyTorque(hkReal deltaTime, const hkVector4& torque) = 0;

    virtual void getMotionStateAndVelocitiesAndDeactivationType(hkpMotion* motionOut);

    hkEnum<MotionType, hkUint8> m_type;
    hkUint8 m_deactivationIntegrateCounter;
    hkUint16 m_deactivationNumInactiveFrames[2];
    hkMotionState m_motionState;
    hkVector4 m_inertiaAndMassInv;
    hkVector4 m_linearVelocity;
    hkVector4 m_angularVelocity;
    hkVector4 m_deactivationRefPosition[2];
    hkUint32 m_deactivationRefOrientation[2];
    hkpMaxSizeMotion* m_savedMotion;
    hkUint16 m_savedQualityTypeIndex;
    hkHalf m_gravityFactor;
};

class hkpRigidMotion : public hkpMotion {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpRigidMotion)

    explicit hkpRigidMotion(hkFinishLoadedObjectFlag flag) : hkpMotion(flag) {}
};
