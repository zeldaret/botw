#pragma once

#include <Havok/Common/Base/hkBase.h>

using hkContactPointId = hkUint16;

constexpr hkContactPointId HK_INVALID_CONTACT_POINT = 0xffff;

class hkContactPoint {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkContactPoint)
    HK_DECLARE_REFLECTION()

    inline const hkVector4& getPosition() const;
    inline void setPosition(const hkVector4& position);

    inline const hkVector4& getNormal() const;
    inline const hkVector4& getSeparatingNormal() const;
    inline void setSeparatingNormal(const hkVector4& normal, hkReal dist);
    inline void setSeparatingNormal(hkVector4Parameter normal, hkSimdRealParameter dist);
    inline void setSeparatingNormal(const hkVector4& separatingNormal);
    inline void setNormalOnly(const hkVector4& normal);

    /// If negative, the two bodies are penetrating.
    inline hkReal getDistance() const;
    inline hkSimdReal getDistanceSimdReal() const;
    inline void setDistance(hkReal d);
    inline void setDistanceSimdReal(hkSimdRealParameter newValue);

    inline void set(const hkVector4& position, const hkVector4& normal, hkReal dist);
    inline void setPositionNormalAndDistance(hkVector4Parameter position, hkVector4Parameter normal,
                                             hkSimdRealParameter dist);

    inline void setFlipped(const hkContactPoint& point);
    inline void flip();

protected:
    hkVector4 m_position;
    // w = distance
    hkVector4 m_separatingNormal;
};

inline const hkVector4& hkContactPoint::getPosition() const {
    return m_position;
}

inline void hkContactPoint::setPosition(const hkVector4& position) {
    m_position = position;
}

inline const hkVector4& hkContactPoint::getNormal() const {
    return m_separatingNormal;
}

inline const hkVector4& hkContactPoint::getSeparatingNormal() const {
    return m_separatingNormal;
}

inline void hkContactPoint::setSeparatingNormal(const hkVector4& normal, hkReal dist) {
    m_separatingNormal = normal;
    m_separatingNormal(3) = dist;
}

inline void hkContactPoint::setSeparatingNormal(hkVector4Parameter normal,
                                                hkSimdRealParameter dist) {
    m_separatingNormal.setXYZ_W(normal, dist);
}

inline void hkContactPoint::setSeparatingNormal(const hkVector4& separatingNormal) {
    m_separatingNormal = separatingNormal;
}

inline void hkContactPoint::setNormalOnly(const hkVector4& normal) {
    m_separatingNormal.setXYZ(normal);
}

inline hkReal hkContactPoint::getDistance() const {
    return m_separatingNormal(3);
}

inline hkSimdReal hkContactPoint::getDistanceSimdReal() const {
    return m_separatingNormal.getComponent<3>();
}

inline void hkContactPoint::setDistance(hkReal d) {
    m_separatingNormal(3) = d;
}

inline void hkContactPoint::setDistanceSimdReal(hkSimdRealParameter newValue) {
    m_separatingNormal.setW(newValue);
}

inline void hkContactPoint::set(const hkVector4& position, const hkVector4& normal, hkReal dist) {
    m_position = position;
    m_separatingNormal = normal;
    m_separatingNormal(3) = dist;
}

inline void hkContactPoint::setPositionNormalAndDistance(hkVector4Parameter position,
                                                         hkVector4Parameter normal,
                                                         hkSimdRealParameter dist) {
    m_position = position;
    m_separatingNormal.setXYZ_W(normal, dist);
}

inline void hkContactPoint::setFlipped(const hkContactPoint& point) {
    m_position.setAddMul(point.m_position, point.m_separatingNormal,
                         point.m_separatingNormal.getComponent<3>());
    m_separatingNormal.setNeg<3>(point.m_separatingNormal);
}

inline void hkContactPoint::flip() {
    setFlipped(*this);
}
