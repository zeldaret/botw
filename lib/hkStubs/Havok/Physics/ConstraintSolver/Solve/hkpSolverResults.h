#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkpSolverResults {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpSolverResults)

    HK_FORCE_INLINE hkReal getImpulseApplied() const;

    hkReal m_impulseApplied = 0.0;
    hkReal m_internalSolverData = 0.0;
};

hkReal hkpSolverResults::getImpulseApplied() const {
    return m_impulseApplied;
}
