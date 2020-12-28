#include "Game/AI/Action/actionChangeWeaponEquipState.h"

namespace uking::action {

ChangeWeaponEquipState::ChangeWeaponEquipState(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ChangeWeaponEquipState::~ChangeWeaponEquipState() = default;

bool ChangeWeaponEquipState::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ChangeWeaponEquipState::loadParams_() {
    getDynamicParam(&mEquipState_d, "EquipState");
}

}  // namespace uking::action
