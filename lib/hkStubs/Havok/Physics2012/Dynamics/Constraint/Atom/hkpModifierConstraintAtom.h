#pragma once

#include <Havok/Physics/Constraint/Atom/hkpConstraintAtom.h>

struct hkpConstraintInfo;

struct hkpModifierConstraintAtom : public hkpConstraintAtom {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpModifierConstraintAtom)
    HK_DECLARE_REFLECTION()

    explicit hkpModifierConstraintAtom(hkFinishLoadedObjectFlag f) : hkpConstraintAtom(f) {}

    int addModifierDataToConstraintInfo(hkpConstraintInfo& cinfo, hkUint8& usedFlagsOut) const;

    static int addAllModifierDataToConstraintInfo(hkpModifierConstraintAtom* firstModifier,
                                                  hkpConstraintInfo& cinfo, hkUint8& usedFlagsOut);

protected:
    hkpModifierConstraintAtom(AtomType type, int size)
        : hkpConstraintAtom(type), m_modifierAtomSize(static_cast<hkUint16>(size)) {}

public:
    alignas(16) hkUint16 m_modifierAtomSize;
    hkUint16 m_childSize;
    hkpConstraintAtom* m_child;
    hkUint32 m_pad[2];
};
