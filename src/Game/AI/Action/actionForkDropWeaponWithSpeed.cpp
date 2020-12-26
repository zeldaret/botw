#include "Game/AI/Action/actionForkDropWeaponWithSpeed.h"

namespace uking::action {

ForkDropWeaponWithSpeed::ForkDropWeaponWithSpeed(const InitArg& arg) : ForkDropWeapon(arg) {}

ForkDropWeaponWithSpeed::~ForkDropWeaponWithSpeed() = default;

bool ForkDropWeaponWithSpeed::init_(sead::Heap* heap) {
    return ForkDropWeapon::init_(heap);
}

void ForkDropWeaponWithSpeed::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkDropWeapon::enter_(params);
}

void ForkDropWeaponWithSpeed::leave_() {
    ForkDropWeapon::leave_();
}

void ForkDropWeaponWithSpeed::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mWeaponDropSpeedXZ_s, "WeaponDropSpeedXZ");
    getStaticParam(&mWeaponDropSpeedY_s, "WeaponDropSpeedY");
    getStaticParam(&mAngleOffsetY_s, "AngleOffsetY");
    getStaticParam(&mChemReset_s, "ChemReset");
}

void ForkDropWeaponWithSpeed::calc_() {
    ForkDropWeapon::calc_();
}

}  // namespace uking::action
