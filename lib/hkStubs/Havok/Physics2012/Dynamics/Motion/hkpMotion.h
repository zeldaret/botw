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

    hkReal getMass() const;
    virtual void setMass(hkReal m);
    virtual void setMass(hkSimdRealParameter m);

    inline hkSimdReal getMassInv() const;
    virtual void setMassInv(hkReal mInv);
    virtual void setMassInv(hkSimdRealParameter mInv);

    virtual void getInertiaLocal(hkMatrix3& inertiaOut) const = 0;
    virtual void getInertiaWorld(hkMatrix3& inertiaOut) const = 0;
    virtual void setInertiaLocal(const hkMatrix3& inertia) = 0;
    virtual void setInertiaInvLocal(const hkMatrix3& inertiaInv) = 0;
    virtual void getInertiaInvLocal(hkMatrix3& inertiaInvOut) const = 0;
    virtual void getInertiaInvWorld(hkMatrix3& inertiaInvOut) const = 0;
    virtual void setCenterOfMassInLocal(const hkVector4& centerOfMass);
    inline const hkVector4& getCenterOfMassLocal() const;
    inline const hkVector4& getCenterOfMassInWorld() const;

    inline hkMotionState* getMotionState();
    inline const hkMotionState* getMotionState() const;

    inline const hkVector4& getPosition() const;
    virtual void setPosition(const hkVector4& position);

    inline const hkQuaternion& getRotation() const;
    virtual void setRotation(const hkQuaternion& rotation);

    virtual void setPositionAndRotation(const hkVector4& position, const hkQuaternion& rotation);

    inline const hkTransform& getTransform() const;
    virtual void setTransform(const hkTransform& transform);
    void approxTransformAt(hkTime time, hkTransform& transformOut);

    inline const hkVector4& getLinearVelocity() const;
    virtual void setLinearVelocity(const hkVector4& newVel);
    inline const hkVector4& getAngularVelocity() const;
    virtual void setAngularVelocity(const hkVector4& newVel);
    inline void getPointVelocity(const hkVector4& p, hkVector4& vecOut) const;
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

    inline hkReal getLinearDamping() const;
    inline void setLinearDamping(hkReal d);
    inline hkReal getAngularDamping() const;
    inline void setAngularDamping(hkReal d);
    inline hkReal getTimeFactor() const;
    inline void setTimeFactor(hkReal f);

    inline hkReal getGravityFactor() const;
    inline void setGravityFactor(hkReal gravityFactor);

    inline int getDeactivationClass() const;
    void setDeactivationClass(int deactivationClass);
    inline void enableDeactivation(bool value, int randomNumber = 0, int worldFlag0 = 0,
                                   int worldFlag1 = 0, int worldDeactivationIntegrateCounter = 0);
    inline bool isDeactivationEnabled() const;
    void requestDeactivation();

    virtual void getMotionStateAndVelocitiesAndDeactivationType(hkpMotion* motionOut);
    inline int getNumInactiveFrames(int select) const;
    inline int getNumInactiveFramesMt(int select,
                                      int worldDeactivationNumInactiveFramesSelectFlag) const;
    inline void setWorldSelectFlagsNeg(int worldFlag0, int worldFlag1,
                                       int worldDeactivationIntegrateCounter);
    inline void incrementNumInactiveFramesMt(int select,
                                             int worldDeactivationNumInactiveFramesSelectFlag);
    inline void zeroNumInactiveFramesMt(int select,
                                        int worldDeactivationNumInactiveFramesSelectFlag);

private:
    void init(const hkVector4& position, const hkQuaternion& rotation,
              bool wantDeactivation = false);

public:
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

inline hkSimdReal hkpMotion::getMassInv() const {
    return m_inertiaAndMassInv.getW();
}

inline const hkVector4& hkpMotion::getCenterOfMassLocal() const {
    return m_motionState.getSweptTransform().m_centerOfMassLocal;
}

inline const hkVector4& hkpMotion::getCenterOfMassInWorld() const {
    return m_motionState.getSweptTransform().m_centerOfMass1;
}

inline hkMotionState* hkpMotion::getMotionState() {
    return &m_motionState;
}

inline const hkMotionState* hkpMotion::getMotionState() const {
    return &m_motionState;
}

inline const hkVector4& hkpMotion::getPosition() const {
    return getTransform().getTranslation();
}

inline const hkQuaternion& hkpMotion::getRotation() const {
    return m_motionState.getSweptTransform().m_rotation1;
}

inline const hkTransform& hkpMotion::getTransform() const {
    return m_motionState.getTransform();
}

inline const hkVector4& hkpMotion::getLinearVelocity() const {
    return m_linearVelocity;
}

inline const hkVector4& hkpMotion::getAngularVelocity() const {
    return m_angularVelocity;
}

inline void hkpMotion::getPointVelocity(const hkVector4& p, hkVector4& vecOut) const {
    hkVector4 relPos;
    relPos.setSub(p, getCenterOfMassInWorld());
    vecOut.setCross(m_angularVelocity, relPos);
    vecOut.add(m_linearVelocity);
}

inline hkReal hkpMotion::getLinearDamping() const {
    return m_motionState.m_linearDamping;
}

inline void hkpMotion::setLinearDamping(hkReal d) {
    m_motionState.m_linearDamping.set<true>(d);
}

inline hkReal hkpMotion::getAngularDamping() const {
    return m_motionState.m_angularDamping;
}

inline void hkpMotion::setAngularDamping(hkReal d) {
    m_motionState.m_angularDamping.set<true>(d);
}

inline hkReal hkpMotion::getTimeFactor() const {
    return m_motionState.m_timeFactor;
}

inline void hkpMotion::setTimeFactor(hkReal f) {
    m_motionState.m_timeFactor.set<true>(f);
}

inline hkReal hkpMotion::getGravityFactor() const {
    return m_gravityFactor;
}

inline void hkpMotion::setGravityFactor(hkReal gravityFactor) {
    m_gravityFactor.set<true>(gravityFactor);
}

inline int hkpMotion::getDeactivationClass() const {
    return m_motionState.m_deactivationClass;
}

inline void hkpMotion::enableDeactivation(bool value, int randomNumber, int worldFlag0,
                                          int worldFlag1, int worldDeactivationIntegrateCounter) {
    if (value) {
        m_deactivationIntegrateCounter = hkUint8(0xf & randomNumber);
        setWorldSelectFlagsNeg(worldFlag0, worldFlag1, worldDeactivationIntegrateCounter);
    } else {
        m_deactivationIntegrateCounter = 0xff;
        for (auto& frame : m_deactivationNumInactiveFrames)
            frame = 0;
    }
}

inline bool hkpMotion::isDeactivationEnabled() const {
    return m_deactivationIntegrateCounter != 0xff;
}

inline int hkpMotion::getNumInactiveFrames(int select) const {
    return m_deactivationNumInactiveFrames[select] & 0x7f;
}

inline int
hkpMotion::getNumInactiveFramesMt(int select,
                                  int worldDeactivationNumInactiveFramesSelectFlag) const {
    int dc = m_deactivationNumInactiveFrames[select];
    int motionDeactivationFlag = dc >> 14;
    if (worldDeactivationNumInactiveFramesSelectFlag != motionDeactivationFlag)
        return dc & 0x7f;
    return (dc >> 7) & 0x7f;
}

inline void hkpMotion::setWorldSelectFlagsNeg(int worldFlag0, int worldFlag1,
                                              int worldDeactivationIntegrateCounter) {
    if (static_cast<unsigned int>(worldDeactivationIntegrateCounter) % 4 <
        static_cast<unsigned int>(m_deactivationIntegrateCounter) % 4) {
        worldFlag0 = ~worldFlag0 << 14;
    } else {
        worldFlag0 <<= 14;
    }

    if (worldDeactivationIntegrateCounter < m_deactivationIntegrateCounter) {
        worldFlag1 = ~worldFlag1 << 14;
    } else {
        worldFlag1 <<= 14;
    }

    m_deactivationNumInactiveFrames[0] =
        hkUint16((m_deactivationNumInactiveFrames[0] & 0x3fff) | worldFlag0);
    m_deactivationNumInactiveFrames[1] =
        hkUint16((m_deactivationNumInactiveFrames[1] & 0x3fff) | worldFlag1);
}

inline void
hkpMotion::incrementNumInactiveFramesMt(int select,
                                        int worldDeactivationNumInactiveFramesSelectFlag) {
    int dc = m_deactivationNumInactiveFrames[select] & 0x7f;
    int newdc = dc + 1 - (dc >> 6);
    dc = newdc | (dc << 7) | (worldDeactivationNumInactiveFramesSelectFlag << 14);
    m_deactivationNumInactiveFrames[select] = hkUint16(dc);
}

inline void hkpMotion::zeroNumInactiveFramesMt(int select,
                                               int worldDeactivationNumInactiveFramesSelectFlag) {
    int dc = m_deactivationNumInactiveFrames[select] & 0x7f;
    dc = (dc << 7) | (worldDeactivationNumInactiveFramesSelectFlag << 14);
    m_deactivationNumInactiveFrames[select] = hkUint16(dc);
}
