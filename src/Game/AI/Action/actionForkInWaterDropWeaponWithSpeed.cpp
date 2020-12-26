#include "Game/AI/Action/actionForkInWaterDropWeaponWithSpeed.h"

namespace uking::action {

ForkInWaterDropWeaponWithSpeed::ForkInWaterDropWeaponWithSpeed(const InitArg& arg)
    : ForkDropWeapon(arg) {}

ForkInWaterDropWeaponWithSpeed::~ForkInWaterDropWeaponWithSpeed() = default;

bool ForkInWaterDropWeaponWithSpeed::init_(sead::Heap* heap) {
    return ForkDropWeapon::init_(heap);
}

void ForkInWaterDropWeaponWithSpeed::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkDropWeapon::enter_(params);
}

void ForkInWaterDropWeaponWithSpeed::leave_() {
    ForkDropWeapon::leave_();
}

void ForkInWaterDropWeaponWithSpeed::loadParams_() {
    ForkDropWeapon::loadParams_();
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mOutWaterDepth_s, "OutWaterDepth");
}

void ForkInWaterDropWeaponWithSpeed::calc_() {
    ForkDropWeapon::calc_();
}

}  // namespace uking::action
