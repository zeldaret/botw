#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkSphere {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkSphere)
    HK_DECLARE_REFLECTION()

    inline hkSphere();
    inline hkSphere(hkVector4Parameter pt, hkReal radius);
    inline hkSphere(hkVector4Parameter pt, hkSimdRealParameter radius);

    inline hkReal getRadius() const;
    inline hkSimdReal getRadiusSimdReal() const;

    inline void setRadius(hkReal newRadius);
    inline void setRadius(hkSimdRealParameter newRadius);

    inline const hkVector4& getPositionAndRadius() const;
    inline hkVector4& getPositionAndRadius();

    inline void setPosition(hkVector4Parameter newPos);
    inline void setPositionAndRadius(hkVector4Parameter newPos);
    inline void setPositionAndRadius(hkVector4Parameter newPos, hkSimdRealParameter newRadius);

protected:
    // the radius is stored in w
    hkVector4 m_pos;
};

inline hkSphere::hkSphere() = default;

inline hkSphere::hkSphere(hkVector4Parameter pt, hkReal radius) {
    m_pos = pt;
    setRadius(radius);
}

inline hkSphere::hkSphere(hkVector4Parameter pt, hkSimdRealParameter radius) {
    m_pos.setXYZ_W(pt, radius);
}

inline hkReal hkSphere::getRadius() const {
    return m_pos(3);
}

inline hkSimdReal hkSphere::getRadiusSimdReal() const {
    return m_pos.getW();
}

inline void hkSphere::setRadius(hkReal newRadius) {
    m_pos(3) = newRadius;
}

inline void hkSphere::setRadius(hkSimdRealParameter newRadius) {
    m_pos.setW(newRadius);
}

inline const hkVector4& hkSphere::getPositionAndRadius() const {
    return m_pos;
}

inline hkVector4& hkSphere::getPositionAndRadius() {
    return m_pos;
}

inline void hkSphere::setPositionAndRadius(const hkVector4f& newPos) {
    m_pos.setXYZ(newPos);
}

inline void hkSphere::setPosition(const hkVector4f& newPos) {
    m_pos = newPos;
}

inline void hkSphere::setPositionAndRadius(const hkVector4f& newPos, const hkSimdReal& newRadius) {
    m_pos.setXYZ_W(newPos, newRadius);
}
