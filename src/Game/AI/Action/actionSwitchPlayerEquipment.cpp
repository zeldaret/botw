#include "Game/AI/Action/actionSwitchPlayerEquipment.h"

namespace uking::action {

SwitchPlayerEquipment::SwitchPlayerEquipment(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SwitchPlayerEquipment::~SwitchPlayerEquipment() = default;

bool SwitchPlayerEquipment::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SwitchPlayerEquipment::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SwitchPlayerEquipment::leave_() {
    ksys::act::ai::Action::leave_();
}

void SwitchPlayerEquipment::loadParams_() {
    getDynamicParam(&mUnequipWeapon_d, "UnequipWeapon");
    getDynamicParam(&mUnequipShield_d, "UnequipShield");
    getDynamicParam(&mUnequipBow_d, "UnequipBow");
    getDynamicParam(&mUnequipArmorHead_d, "UnequipArmorHead");
    getDynamicParam(&mUnequipArmorUpper_d, "UnequipArmorUpper");
    getDynamicParam(&mUnequipArmorLower_d, "UnequipArmorLower");
    getDynamicParam(&mPorchItemName_Weapon_d, "PorchItemName_Weapon");
    getDynamicParam(&mPorchItemName_Shield_d, "PorchItemName_Shield");
    getDynamicParam(&mPorchItemName_Bow_d, "PorchItemName_Bow");
    getDynamicParam(&mPorchItemName_ArmorHead_d, "PorchItemName_ArmorHead");
    getDynamicParam(&mPorchItemName_ArmorUpper_d, "PorchItemName_ArmorUpper");
    getDynamicParam(&mPorchItemName_ArmorLower_d, "PorchItemName_ArmorLower");
    getDynamicParam(&mPorchItemName_Arrow_d, "PorchItemName_Arrow");
}

void SwitchPlayerEquipment::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
