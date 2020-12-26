#include "Game/AI/Action/actionSetChemicalWeaponPower.h"

namespace uking::action {

SetChemicalWeaponPower::SetChemicalWeaponPower(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetChemicalWeaponPower::~SetChemicalWeaponPower() = default;

bool SetChemicalWeaponPower::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetChemicalWeaponPower::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SetChemicalWeaponPower::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetChemicalWeaponPower::loadParams_() {}

void SetChemicalWeaponPower::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
