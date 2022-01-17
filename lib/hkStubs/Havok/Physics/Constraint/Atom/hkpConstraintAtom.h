#pragma once

#include <Havok/Common/Base/hkBase.h>

struct hkpConstraintAtom {
public:
    enum AtomType {
        TYPE_INVALID = 0,

        TYPE_BRIDGE,  // 1

        TYPE_SET_LOCAL_TRANSFORMS,    // 2
        TYPE_SET_LOCAL_TRANSLATIONS,  // 3
        TYPE_SET_LOCAL_ROTATIONS,     // 4

        TYPE_BALL_SOCKET,   // 5
        TYPE_STIFF_SPRING,  // 6

        TYPE_LIN,           // 7
        TYPE_LIN_SOFT,      // 8
        TYPE_LIN_LIMIT,     // 9
        TYPE_LIN_FRICTION,  // 10
        TYPE_LIN_MOTOR,     // 11

        TYPE_2D_ANG,  // 12

        TYPE_ANG,           // 13
        TYPE_ANG_LIMIT,     // 14
        TYPE_TWIST_LIMIT,   // 15
        TYPE_CONE_LIMIT,    // 16
        TYPE_ANG_FRICTION,  // 17
        TYPE_ANG_MOTOR,     // 18

        TYPE_RAGDOLL_MOTOR,  // 19

        TYPE_PULLEY,           // 20
        TYPE_RACK_AND_PINION,  // 21
        TYPE_COG_WHEEL,        // 22

        TYPE_SETUP_STABILIZATION,  // 23
        TYPE_3D_ANG,               // 24
        TYPE_DEFORMABLE_3D_LIN,    // 25
        TYPE_DEFORMABLE_3D_ANG,    // 26

        TYPE_OVERWRITE_PIVOT,

        TYPE_WHEEL_FRICTION,  // 28

        TYPE_CONTACT,

        FIRST_MODIFIER_TYPE,
        TYPE_MODIFIER_SOFT_CONTACT = FIRST_MODIFIER_TYPE,
        TYPE_MODIFIER_MASS_CHANGER,
        TYPE_MODIFIER_VISCOUS_SURFACE,
        TYPE_MODIFIER_MOVING_SURFACE,
        TYPE_MODIFIER_IGNORE_CONSTRAINT,
        TYPE_MODIFIER_CENTER_OF_MASS_CHANGER,
        LAST_MODIFIER_TYPE = TYPE_MODIFIER_CENTER_OF_MASS_CHANGER,

        TYPE_MAX
    };

    enum CallbackRequest {
        CALLBACK_REQUEST_NONE = 0,
        CALLBACK_REQUEST_NEW_CONTACT_POINT = 1,
        CALLBACK_REQUEST_SETUP_PPU_ONLY = 2,
        CALLBACK_REQUEST_SETUP_CALLBACK = 4,
        CALLBACK_REQUEST_CONTACT_POINT_CALLBACK = 8
    };

    enum SolvingMethod {
        METHOD_STABILIZED = 0,
        METHOD_OLD = 1,
    };

    HK_DECLARE_CLASS_ALLOCATOR(hkpConstraintAtom)
    HK_DECLARE_REFLECTION()

    hkpConstraintAtom() = delete;
    explicit hkpConstraintAtom(hkFinishLoadedObjectFlag f) {}

    HK_FORCE_INLINE AtomType getType() const { return m_type; }
    HK_FORCE_INLINE int isModifierType() const { return m_type >= FIRST_MODIFIER_TYPE; }

protected:
    hkpConstraintAtom(AtomType type) : m_type(type) {}

public:
    hkEnum<AtomType, hkUint16> m_type;
};
