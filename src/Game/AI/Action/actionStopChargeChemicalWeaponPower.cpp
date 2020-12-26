#include "Game/AI/Action/actionStopChargeChemicalWeaponPower.h"

namespace uking::action {

StopChargeChemicalWeaponPower::StopChargeChemicalWeaponPower(const InitArg& arg)
    : SetChemicalWeaponPower(arg) {}

StopChargeChemicalWeaponPower::~StopChargeChemicalWeaponPower() = default;

bool StopChargeChemicalWeaponPower::init_(sead::Heap* heap) {
    return SetChemicalWeaponPower::init_(heap);
}

void StopChargeChemicalWeaponPower::enter_(ksys::act::ai::InlineParamPack* params) {
    SetChemicalWeaponPower::enter_(params);
}

void StopChargeChemicalWeaponPower::leave_() {
    SetChemicalWeaponPower::leave_();
}

void StopChargeChemicalWeaponPower::loadParams_() {
    SetChemicalWeaponPower::loadParams_();
}

void StopChargeChemicalWeaponPower::calc_() {
    SetChemicalWeaponPower::calc_();
}

}  // namespace uking::action
