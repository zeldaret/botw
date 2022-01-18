#pragma once

#include <Havok/Common/Base/hkBase.h>

/// Axis aligned bounding box
// FIXME: incomplete
class hkAabb {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkAabb)

    hkAabb() {}
    HK_FORCE_INLINE hkAabb(const hkVector4& min, const hkVector4& max) : m_min(min), m_max(max) {}

    HK_FORCE_INLINE void getExtents(hkVector4& e) const;
    HK_FORCE_INLINE void getCenter(hkVector4& center) const;

    hkVector4 m_min;
    hkVector4 m_max;
};

inline void hkAabb::getExtents(hkVector4& e) const {
    e.setSub(m_max, m_min);
}

inline void hkAabb::getCenter(hkVector4& center) const {
    hkVector4 s;
    s.setAdd(m_min, m_max);
    center.setMul(s, hkSimdReal::getConstant<HK_QUADREAL_INV_2>());
}
