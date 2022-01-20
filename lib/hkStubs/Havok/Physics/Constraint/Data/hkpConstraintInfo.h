#pragma once

#include <Havok/Common/Base/hkBase.h>

struct hkpConstraintInfo {
    HK_DECLARE_CLASS_ALLOCATOR(hkpConstraintInfo)

    inline void add(int schemaSize, int numSolverResults, int numSolverTempElems);
    inline void add(const hkpConstraintInfo& delta);
    inline void sub(const hkpConstraintInfo& delta);

    int m_maxSizeOfSchema;
    int m_sizeOfSchemas;
    int m_numSolverResults;
    int m_numSolverElemTemps;
};

inline void hkpConstraintInfo::add(int schemaSize, int numSolverResults, int numSolverTempElems) {
    m_sizeOfSchemas += schemaSize;
    m_numSolverResults += numSolverResults;
    m_numSolverElemTemps += numSolverTempElems;
}

inline void hkpConstraintInfo::add(const hkpConstraintInfo& delta) {
    m_maxSizeOfSchema = hkMath::max2(m_maxSizeOfSchema, delta.m_maxSizeOfSchema);
    m_maxSizeOfSchema = hkMath::max2(m_maxSizeOfSchema, delta.m_sizeOfSchemas);
    m_sizeOfSchemas += delta.m_sizeOfSchemas;
    m_numSolverResults += delta.m_numSolverResults;
    m_numSolverElemTemps += delta.m_numSolverElemTemps;
}

inline void hkpConstraintInfo::sub(const hkpConstraintInfo& delta) {
    m_sizeOfSchemas -= delta.m_sizeOfSchemas;
    m_numSolverResults -= delta.m_numSolverResults;
    m_numSolverElemTemps -= delta.m_numSolverElemTemps;
}
