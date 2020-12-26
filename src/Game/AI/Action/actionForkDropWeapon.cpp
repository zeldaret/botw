#include "Game/AI/Action/actionForkDropWeapon.h"

namespace uking::action {

ForkDropWeapon::ForkDropWeapon(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkDropWeapon::~ForkDropWeapon() = default;

bool ForkDropWeapon::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkDropWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkDropWeapon::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkDropWeapon::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mWeaponDropSpeedXZ_s, "WeaponDropSpeedXZ");
    getStaticParam(&mWeaponDropSpeedY_s, "WeaponDropSpeedY");
    getStaticParam(&mAngleOffsetY_s, "AngleOffsetY");
    getStaticParam(&mChemReset_s, "ChemReset");
}

void ForkDropWeapon::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
