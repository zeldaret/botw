#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkSweptTransformf {
public:
    hkSweptTransformf() {}

    HK_FORCE_INLINE hkTime getBaseTime() const;
    HK_FORCE_INLINE hkSimdFloat32 getBaseTimeSr() const;

    HK_FORCE_INLINE hkFloat32 getInvDeltaTime() const;
    HK_FORCE_INLINE hkSimdFloat32 getInvDeltaTimeSr() const;

    hkVector4f m_centerOfMass0;
    hkVector4f m_centerOfMass1;
    hkQuaternionf m_rotation0;
    hkQuaternionf m_rotation1;
    hkVector4f m_centerOfMassLocal;
};

inline hkTime hkSweptTransformf::getBaseTime() const {
    return static_cast<hkTime>(m_centerOfMass0(3));
}

inline hkSimdFloat32 hkSweptTransformf::getBaseTimeSr() const {
    return m_centerOfMass0.getComponent<3>();
}

inline hkFloat32 hkSweptTransformf::getInvDeltaTime() const {
    return m_centerOfMass1(3);
}

inline hkSimdFloat32 hkSweptTransformf::getInvDeltaTimeSr() const {
    return m_centerOfMass1.getComponent<3>();
}
