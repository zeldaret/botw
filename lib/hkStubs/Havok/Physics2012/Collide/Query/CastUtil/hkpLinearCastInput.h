#pragma once

#include <Havok/Common/Base/hkBase.h>

struct hkpLinearCastInput {
    HK_DECLARE_CLASS_ALLOCATOR(hkpLinearCastInput)

    hkVector4 m_to;
    hkReal m_maxExtraPenetration = HK_REAL_EPSILON;
    hkReal m_startPointTolerance = HK_REAL_EPSILON;
};
