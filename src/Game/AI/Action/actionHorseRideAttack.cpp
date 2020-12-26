#include "Game/AI/Action/actionHorseRideAttack.h"

namespace uking::action {

HorseRideAttack::HorseRideAttack(const InitArg& arg) : HorseRideLookWait(arg) {}

HorseRideAttack::~HorseRideAttack() = default;

bool HorseRideAttack::init_(sead::Heap* heap) {
    return HorseRideLookWait::init_(heap);
}

void HorseRideAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideLookWait::enter_(params);
}

void HorseRideAttack::leave_() {
    HorseRideLookWait::leave_();
}

void HorseRideAttack::loadParams_() {
    HorseRideLookWait::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mJustAvoidSideDist_s, "JustAvoidSideDist");
    getStaticParam(&mJustAvoidBackDist_s, "JustAvoidBackDist");
    getStaticParam(&mJustAvoidAngle_s, "JustAvoidAngle");
}

void HorseRideAttack::calc_() {
    HorseRideLookWait::calc_();
}

}  // namespace uking::action
