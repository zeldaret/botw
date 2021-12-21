#pragma once

#include <Havok/Common/Base/hkBase.h>

struct hkpWorldRayCastInput {
    HK_DECLARE_CLASS_ALLOCATOR(hkpWorldRayCastInput)

    hkVector4 m_from;
    hkVector4 m_to;
    hkBool m_enableShapeCollectionFilter = false;
    hkUint32 m_filterInfo = 0;
    hkUlong m_userData = 0;
};
