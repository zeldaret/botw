#include "Game/AI/Action/actionChangeWeaponEquipState.h"

namespace uking::action {

ChangeWeaponEquipState::ChangeWeaponEquipState(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ChangeWeaponEquipState::~ChangeWeaponEquipState() = default;

bool ChangeWeaponEquipState::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ChangeWeaponEquipState::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ChangeWeaponEquipState::leave_() {
    ksys::act::ai::Action::leave_();
}

void ChangeWeaponEquipState::loadParams_() {
    getDynamicParam(&mEquipState_d, "EquipState");
}

void ChangeWeaponEquipState::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
