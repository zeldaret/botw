#pragma once

#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Dynamics/Motion/hkpMotion.h>

class hkpSphereMotion : public hkpMotion {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpSphereMotion)
    HK_DECLARE_REFLECTION()

    hkpSphereMotion(const hkVector4& position, const hkQuaternion& rotation)
        : hkpMotion(position, rotation) {
        m_type = MOTION_SPHERE_INERTIA;
    }

    explicit hkpSphereMotion(hkFinishLoadedObjectFlag flag) : hkpMotion(flag) {}

    void getInertiaLocal(hkMatrix3& inertia) const override;
    void getInertiaWorld(hkMatrix3& inertia) const override;
    void setInertiaLocal(const hkMatrix3& inertia) override;
    void setInertiaInvLocal(const hkMatrix3& inertiaInv) override;
    void getInertiaInvLocal(hkMatrix3& inertiaInv) const override;
    void getInertiaInvWorld(hkMatrix3& inertiaInv) const override;
    void getProjectedPointVelocity(const hkVector4& p, const hkVector4& normal, hkReal& velOut,
                                   hkReal& invVirtMassOut) const override;
    void getProjectedPointVelocitySimd(const hkVector4& p, const hkVector4& normal,
                                       hkSimdReal& velOut,
                                       hkSimdReal& invVirtMassOut) const override;
    void applyPointImpulse(const hkVector4& imp, const hkVector4& p) override;
    void applyAngularImpulse(const hkVector4& imp) override;
    void applyForce(const hkReal deltaTime, const hkVector4& force) override;
    void applyForce(const hkReal deltaTime, const hkVector4& force, const hkVector4& p) override;
    void applyTorque(const hkReal deltaTime, const hkVector4& torque) override;
};
