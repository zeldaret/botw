#include "Game/AI/Action/actionEquipedQuiver.h"

namespace uking::action {

EquipedQuiver::EquipedQuiver(const InitArg& arg) : EquipedOptionalWeaponAction(arg) {}

EquipedQuiver::~EquipedQuiver() = default;

void EquipedQuiver::enter_(ksys::act::ai::InlineParamPack* params) {
    EquipedOptionalWeaponAction::enter_(params);
}

void EquipedQuiver::calc_() {
    EquipedOptionalWeaponAction::calc_();
}

}  // namespace uking::action
