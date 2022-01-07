#pragma once

#include <Havok/Common/Base/Math/SweptTransform/hkSweptTransform.h>
#include <Havok/Common/Base/hkBase.h>

class hkMotionState {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkMotionState)
    HK_DECLARE_REFLECTION()

    inline hkMotionState();

    void initMotionState(const hkVector4& position, const hkQuaternion& rotation);

    inline hkTransform& getTransform();
    inline const hkTransform& getTransform() const;

    inline hkSweptTransform& getSweptTransform();
    inline const hkSweptTransform& getSweptTransform() const;

protected:
    hkTransform m_transform;
    hkSweptTransform m_sweptTransform;

public:
    hkVector4 m_deltaAngle;
    hkReal m_objectRadius;
    hkHalf m_linearDamping;
    hkHalf m_angularDamping;
    hkHalf m_timeFactor;
    hkUFloat8 m_maxLinearVelocity;
    hkUFloat8 m_maxAngularVelocity;
    hkUint8 m_deactivationClass;
};

inline hkMotionState::hkMotionState() = default;

inline hkTransform& hkMotionState::getTransform() {
    return m_transform;
}

inline const hkTransform& hkMotionState::getTransform() const {
    return m_transform;
}

inline hkSweptTransform& hkMotionState::getSweptTransform() {
    return m_sweptTransform;
}

inline const hkSweptTransform& hkMotionState::getSweptTransform() const {
    return m_sweptTransform;
}
