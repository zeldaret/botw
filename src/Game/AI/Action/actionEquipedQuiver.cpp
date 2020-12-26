#include "Game/AI/Action/actionEquipedQuiver.h"

namespace uking::action {

EquipedQuiver::EquipedQuiver(const InitArg& arg) : EquipedOptionalWeaponAction(arg) {}

EquipedQuiver::~EquipedQuiver() = default;

bool EquipedQuiver::init_(sead::Heap* heap) {
    return EquipedOptionalWeaponAction::init_(heap);
}

void EquipedQuiver::enter_(ksys::act::ai::InlineParamPack* params) {
    EquipedOptionalWeaponAction::enter_(params);
}

void EquipedQuiver::leave_() {
    EquipedOptionalWeaponAction::leave_();
}

void EquipedQuiver::loadParams_() {}

void EquipedQuiver::calc_() {
    EquipedOptionalWeaponAction::calc_();
}

}  // namespace uking::action
