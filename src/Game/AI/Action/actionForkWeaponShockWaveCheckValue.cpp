#include "Game/AI/Action/actionForkWeaponShockWaveCheckValue.h"

namespace uking::action {

ForkWeaponShockWaveCheckValue::ForkWeaponShockWaveCheckValue(const InitArg& arg)
    : ForkWeaponShockWave(arg) {}

ForkWeaponShockWaveCheckValue::~ForkWeaponShockWaveCheckValue() = default;

bool ForkWeaponShockWaveCheckValue::init_(sead::Heap* heap) {
    return ForkWeaponShockWave::init_(heap);
}

void ForkWeaponShockWaveCheckValue::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkWeaponShockWave::enter_(params);
}

void ForkWeaponShockWaveCheckValue::leave_() {
    ForkWeaponShockWave::leave_();
}

void ForkWeaponShockWaveCheckValue::loadParams_() {
    ForkWeaponShockWave::loadParams_();
    getStaticParam(&mAtEventValue_s, "AtEventValue");
}

void ForkWeaponShockWaveCheckValue::calc_() {
    ForkWeaponShockWave::calc_();
}

}  // namespace uking::action
