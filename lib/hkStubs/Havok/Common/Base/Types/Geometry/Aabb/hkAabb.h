#pragma once

#include <Havok/Common/Base/hkBase.h>

/// Axis aligned bounding box
// FIXME: incomplete
class hkAabb {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkAabb)

    hkAabb() {}
    HK_FORCE_INLINE hkAabb(const hkVector4& min, const hkVector4& max) : m_min(min), m_max(max) {}

    hkVector4 m_min;
    hkVector4 m_max;
};
