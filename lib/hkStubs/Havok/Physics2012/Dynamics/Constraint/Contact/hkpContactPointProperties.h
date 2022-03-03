#pragma once

#include <Havok/Common/Base/Types/Physics/ContactPoint/hkContactPointMaterial.h>
#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics/ConstraintSolver/Solve/hkpSolverResults.h>

struct hkpSimpleContactConstraintAtom;

class hkpContactPointProperties : public hkpSolverResults, public hkContactPointMaterial {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpContactPointProperties)

    using UserData = hkUint32;

    hkReal m_internalDataA;
};
