#include "Game/AI/Action/actionEquipedChemicalWeapon.h"

namespace uking::action {

EquipedChemicalWeapon::EquipedChemicalWeapon(const InitArg& arg) : EquipedAction(arg) {}

EquipedChemicalWeapon::~EquipedChemicalWeapon() = default;

void EquipedChemicalWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    EquipedAction::enter_(params);
}

void EquipedChemicalWeapon::calc_() {
    EquipedAction::calc_();
}

}  // namespace uking::action
