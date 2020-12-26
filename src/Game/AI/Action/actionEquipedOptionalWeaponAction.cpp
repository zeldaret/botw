#include "Game/AI/Action/actionEquipedOptionalWeaponAction.h"

namespace uking::action {

EquipedOptionalWeaponAction::EquipedOptionalWeaponAction(const InitArg& arg) : BindAction(arg) {}

EquipedOptionalWeaponAction::~EquipedOptionalWeaponAction() = default;

bool EquipedOptionalWeaponAction::init_(sead::Heap* heap) {
    return BindAction::init_(heap);
}

void EquipedOptionalWeaponAction::enter_(ksys::act::ai::InlineParamPack* params) {
    BindAction::enter_(params);
}

void EquipedOptionalWeaponAction::leave_() {
    BindAction::leave_();
}

void EquipedOptionalWeaponAction::loadParams_() {}

void EquipedOptionalWeaponAction::calc_() {
    BindAction::calc_();
}

}  // namespace uking::action
