#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkpCollidable;
class hkpRayShapeCollectionFilter;

struct hkpShapeRayCastInput {
    HK_DECLARE_CLASS_ALLOCATOR(hkpShapeRayCastInput)

    hkVector4 m_from;
    hkVector4 m_to;
    hkUint32 m_filterInfo = 0;
    const hkpRayShapeCollectionFilter* m_rayShapeCollectionFilter = nullptr;
    const hkpCollidable* m_collidable = nullptr;
    hkUlong m_userData = 0;
};
