#pragma once

#include <Havok/Common/Base/Types/Physics/ContactPoint/hkContactPoint.h>
#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics/Constraint/Atom/hkpConstraintAtom.h>
#include <Havok/Physics/Constraint/Data/hkpConstraintInfo.h>
#include <Havok/Physics2012/Internal/Solver/Contact/hkpSimpleContactConstraintDataInfo.h>

class hkpContactPointProperties;

struct hkpSimpleContactConstraintAtom : public hkpConstraintAtom {
public:
    HK_DECLARE_REFLECTION()
    HK_DECLARE_CLASS_ALLOCATOR(hkpSimpleContactConstraintAtom)

    hkpSimpleContactConstraintAtom() : hkpConstraintAtom(TYPE_CONTACT) {}
    explicit hkpSimpleContactConstraintAtom(hkFinishLoadedObjectFlag f);

    HK_FORCE_INLINE hkContactPoint* getContactPoints() const {
        return const_cast<hkContactPoint*>(reinterpret_cast<const hkContactPoint*>(this + 1));
    }

    HK_FORCE_INLINE int getContactPointPropertiesStriding() const;

    HK_FORCE_INLINE hkpContactPointProperties* getContactPointPropertiesStream() const {
        return const_cast<hkpContactPointProperties*>(
            reinterpret_cast<const hkpContactPointProperties*>(hkAddByteOffsetConst(
                getContactPoints(), sizeof(hkContactPoint) * m_numReservedContactPoints)));
    }

    HK_FORCE_INLINE hkpContactPointProperties* getContactPointPropertiesStream(int i) const;

    HK_FORCE_INLINE hkpConstraintAtom* next() const { return nullptr; }
    HK_FORCE_INLINE int numSolverResults() const { return m_numContactPoints + 3; }
    HK_FORCE_INLINE void addToConstraintInfo(hkpConstraintInfo& infoOut) const;

    hkUint16 m_sizeOfAllAtoms;
    hkUint16 m_numContactPoints;
    hkUint16 m_numReservedContactPoints;

    hkUint8 m_numUserDatasForBodyA;
    hkUint8 m_numUserDatasForBodyB;
    hkUint8 m_contactPointPropertiesStriding;
    hkUint16 m_maxNumContactPoints;

    alignas(16) hkpSimpleContactConstraintDataInfo m_info;
};
