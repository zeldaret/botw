#pragma once

#include <Havok/Common/Base/hkBase.h>

struct hkpConstraintInfo {
    HK_DECLARE_CLASS_ALLOCATOR(hkpConstraintInfo)

    int m_maxSizeOfSchema;
    int m_sizeOfSchemas;
    int m_numSolverResults;
    int m_numSolverElemTemps;
};
