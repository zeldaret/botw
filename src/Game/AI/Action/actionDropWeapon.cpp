#include "Game/AI/Action/actionDropWeapon.h"

namespace uking::action {

DropWeapon::DropWeapon(const InitArg& arg) : OnetimeStopASPlay(arg) {}

DropWeapon::~DropWeapon() = default;

bool DropWeapon::init_(sead::Heap* heap) {
    return OnetimeStopASPlay::init_(heap);
}

void DropWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
}

void DropWeapon::leave_() {
    OnetimeStopASPlay::leave_();
}

void DropWeapon::loadParams_() {
    OnetimeStopASPlay::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mWeaponDropSpeedXZ_s, "WeaponDropSpeedXZ");
    getStaticParam(&mWeaponDropSpeedY_s, "WeaponDropSpeedY");
    getStaticParam(&mAngleOffsetY_s, "AngleOffsetY");
    getStaticParam(&mChemReset_s, "ChemReset");
}

void DropWeapon::calc_() {
    OnetimeStopASPlay::calc_();
}

}  // namespace uking::action
