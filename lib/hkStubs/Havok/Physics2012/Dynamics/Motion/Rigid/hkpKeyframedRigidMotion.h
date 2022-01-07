#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Dynamics/Motion/hkpMotion.h>

class hkpKeyframedRigidMotion : public hkpMotion {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpKeyframedRigidMotion)
    HK_DECLARE_REFLECTION()

    hkpKeyframedRigidMotion(const hkVector4& position, const hkQuaternion& rotation);
    explicit hkpKeyframedRigidMotion(hkFinishLoadedObjectFlag flag) : hkpMotion(flag) {}
    ~hkpKeyframedRigidMotion() override;

    void setMass(hkReal m) override;
    void setMass(hkSimdRealParameter m) override;

    void setMassInv(hkReal mInv) override;
    void setMassInv(hkSimdRealParameter mInv) override;

    void getInertiaLocal(hkMatrix3& inertia) const override;
    void setInertiaLocal(const hkMatrix3& inertia) override;
    void getInertiaWorld(hkMatrix3& inertiaOut) const override;
    void setInertiaInvLocal(const hkMatrix3& inertiaInv) override;
    void getInertiaInvLocal(hkMatrix3& inertiaInv) const override;
    void getInertiaInvWorld(hkMatrix3& inertiaInvOut) const override;

    void getProjectedPointVelocity(const hkVector4& p, const hkVector4& normal, hkReal& velOut,
                                   hkReal& invVirtMassOut) const override;
    void getProjectedPointVelocitySimd(const hkVector4& p, const hkVector4& normal,
                                       hkSimdReal& velOut,
                                       hkSimdReal& invVirtMassOut) const override;

    void applyLinearImpulse(const hkVector4& imp) override;
    void applyPointImpulse(const hkVector4& imp, const hkVector4& p) override;
    void applyAngularImpulse(const hkVector4& imp) override;

    void applyForce(const hkReal deltaTime, const hkVector4& force) override;
    void applyForce(const hkReal deltaTime, const hkVector4& force, const hkVector4& p) override;
    void applyTorque(const hkReal deltaTime, const hkVector4& torque) override;

    virtual void setStepPosition(hkReal position, hkReal timestep);
    virtual void setStoredMotion(hkpMaxSizeMotion* savedMotion);

protected:
    hkpKeyframedRigidMotion() : hkpMotion() { m_savedMotion = nullptr; }
};

class hkpMaxSizeMotion : public hkpKeyframedRigidMotion {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpMaxSizeMotion)
    HK_DECLARE_REFLECTION()

    hkpMaxSizeMotion() : hkpKeyframedRigidMotion() {}
    explicit hkpMaxSizeMotion(hkFinishLoadedObjectFlag flag) : hkpKeyframedRigidMotion(flag) {}

    hkpMaxSizeMotion(const hkpMaxSizeMotion&) = delete;
    auto operator=(const hkpMaxSizeMotion&) = delete;
};
