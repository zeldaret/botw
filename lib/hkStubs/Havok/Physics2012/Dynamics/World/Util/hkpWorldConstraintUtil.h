#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics/Constraint/Atom/hkpConstraintAtom.h>

struct hkConstraintInternal;

class hkpConstraintInstance;
class hkpConstraintOwner;
class hkpEntity;
struct hkpModifierConstraintAtom;
class hkpWorld;

class hkpWorldConstraintUtil {
public:
    static void addConstraint(hkpWorld* world, hkpConstraintInstance* constraint);

    static void removeConstraint(hkpConstraintInstance* constraint);

    static hkpConstraintInstance* getConstraint(const hkpEntity* entityA, const hkpEntity* entityB);

    static void addModifier(hkpConstraintInstance* instance, hkpConstraintOwner& constraintOwner,
                            hkpModifierConstraintAtom* s);

    static void removeAndDeleteModifier(hkpConstraintInstance* instance,
                                        hkpConstraintOwner& constraintOwner,
                                        hkpConstraintAtom::AtomType type);

    static hkpModifierConstraintAtom* findModifier(hkpConstraintInstance* instance,
                                                   hkpConstraintAtom::AtomType type);

    static hkpModifierConstraintAtom* findLastModifier(hkpConstraintInstance* instance);

    static void updateFatherOfMovedAtom(hkpConstraintInstance* instance,
                                        const hkpConstraintAtom* oldAtom,
                                        const hkpConstraintAtom* updatedAtom,
                                        int updatedSizeOfAtom);

    HK_FORCE_INLINE static hkpConstraintAtom*
    getTerminalAtom(const hkConstraintInternal* cInternal);
};
