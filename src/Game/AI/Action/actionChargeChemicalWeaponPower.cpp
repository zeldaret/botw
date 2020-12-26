#include "Game/AI/Action/actionChargeChemicalWeaponPower.h"

namespace uking::action {

ChargeChemicalWeaponPower::ChargeChemicalWeaponPower(const InitArg& arg)
    : SetChemicalWeaponPower(arg) {}

ChargeChemicalWeaponPower::~ChargeChemicalWeaponPower() = default;

bool ChargeChemicalWeaponPower::init_(sead::Heap* heap) {
    return SetChemicalWeaponPower::init_(heap);
}

void ChargeChemicalWeaponPower::enter_(ksys::act::ai::InlineParamPack* params) {
    SetChemicalWeaponPower::enter_(params);
}

void ChargeChemicalWeaponPower::leave_() {
    SetChemicalWeaponPower::leave_();
}

void ChargeChemicalWeaponPower::loadParams_() {
    SetChemicalWeaponPower::loadParams_();
}

void ChargeChemicalWeaponPower::calc_() {
    SetChemicalWeaponPower::calc_();
}

}  // namespace uking::action
