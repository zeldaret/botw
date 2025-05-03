#pragma once

#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
namespace uking::ui {

class PouchItem;
enum class PouchItemType;
enum class EquipmentSlot;

}  // namespace uking::ui

namespace uking::act {
struct WeaponModifierInfo;

enum class CreateEquipmentSlot : u8 {
    WeaponSword = 0,
    WeaponShield = 1,
    WeaponBow = 2,
    ArmorHead = 3,
    ArmorUpper = 4,
    ArmorLower = 5,
    Length = 6,
};

class CreatePlayerEquipActorMgr {
    SEAD_SINGLETON_DISPOSER(CreatePlayerEquipActorMgr)
    CreatePlayerEquipActorMgr();
    virtual ~CreatePlayerEquipActorMgr();

public:
    // TODO 0x71006669F8
    void doRequestCreateWeapon(int slot_idx, const sead::SafeString& name, int value,
                               const WeaponModifierInfo* modifier, const sead::SafeString& caller);

    // TODO 0x7100666CF8
    void doRequestCreateArmor(int slot_idx, const sead::SafeString& name, int dye_color,
                              const sead::SafeString& caller);

    void requestCreateDefaultArmor(s32 slot_idx, const sead::SafeString& caller);
    void requestCreateArmorHeadB(const sead::SafeString& name, int dye_color,
                                 const sead::SafeString& caller);
};

bool needsArmorHeadB(const sead::SafeString& armor_head_name,
                     const sead::SafeString& armor_upper_name);
CreateEquipmentSlot getCreateEquipmentSlot(ui::PouchItemType type);
ui::EquipmentSlot getEquipmentSlot(CreateEquipmentSlot slot);
bool createEquipmentFromItem(const ui::PouchItem* item, const sead::SafeString& caller);

}  // namespace uking::act
