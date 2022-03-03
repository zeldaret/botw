#pragma once

#include <Havok/Physics2012/Dynamics/Constraint/Atom/hkpSimpleContactConstraintAtom.h>

class hkpSimpleContactConstraintAtomUtil {
public:
    static hkpSimpleContactConstraintAtom*
    expandOne(hkpSimpleContactConstraintAtom* oldAtom_mightGetDeallocated, bool& atomReallocated);

    inline static void removeAtAndCopy(hkpSimpleContactConstraintAtom* atom, int index);

    static hkpSimpleContactConstraintAtom*
    optimizeCapacity(hkpSimpleContactConstraintAtom* oldAtom_mightGetDeallocated,
                     int numFreeElemsLeft, bool& atomReallocated);

    static hkpSimpleContactConstraintAtom* allocateAtom(int numReservedContactPoints,
                                                        int numExtraUserDatasA,
                                                        int numExtraUserDatasB,
                                                        int maxNumContactPoints);

    static void copyContents(hkpSimpleContactConstraintAtom* dst,
                             const hkpSimpleContactConstraintAtom* src);

    static inline void deallocateAtom(hkpSimpleContactConstraintAtom* atom);

    static inline int calculateAtomSize(int numReservedContactPoints, int numExtraUserDatas);
};

void hkpSimpleContactConstraintAtomUtil::deallocateAtom(hkpSimpleContactConstraintAtom* atom) {
    extern int atomSizeRoundUp(int);
    int allocsize = atomSizeRoundUp(atom->m_sizeOfAllAtoms);
    hkDeallocateChunk(reinterpret_cast<char*>(atom), allocsize);
}
