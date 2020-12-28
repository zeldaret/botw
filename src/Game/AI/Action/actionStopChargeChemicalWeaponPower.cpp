#include "Game/AI/Action/actionStopChargeChemicalWeaponPower.h"

namespace uking::action {

StopChargeChemicalWeaponPower::StopChargeChemicalWeaponPower(const InitArg& arg)
    : SetChemicalWeaponPower(arg) {}

StopChargeChemicalWeaponPower::~StopChargeChemicalWeaponPower() = default;

bool StopChargeChemicalWeaponPower::init_(sead::Heap* heap) {
    return SetChemicalWeaponPower::init_(heap);
}

void StopChargeChemicalWeaponPower::loadParams_() {
    SetChemicalWeaponPower::loadParams_();
}

}  // namespace uking::action
