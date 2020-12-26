#include "Game/AI/Action/actionEquipedChemicalWeapon.h"

namespace uking::action {

EquipedChemicalWeapon::EquipedChemicalWeapon(const InitArg& arg) : EquipedAction(arg) {}

EquipedChemicalWeapon::~EquipedChemicalWeapon() = default;

bool EquipedChemicalWeapon::init_(sead::Heap* heap) {
    return EquipedAction::init_(heap);
}

void EquipedChemicalWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    EquipedAction::enter_(params);
}

void EquipedChemicalWeapon::leave_() {
    EquipedAction::leave_();
}

void EquipedChemicalWeapon::loadParams_() {
    getDynamicParam(&mNodeName_d, "NodeName");
    getDynamicParam(&mRotOffset_d, "RotOffset");
    getDynamicParam(&mTransOffset_d, "TransOffset");
}

void EquipedChemicalWeapon::calc_() {
    EquipedAction::calc_();
}

}  // namespace uking::action
