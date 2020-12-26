#include "Game/AI/Action/actionWeaponHold.h"

namespace uking::action {

WeaponHold::WeaponHold(const InitArg& arg) : OnetimeStopASPlay(arg) {}

WeaponHold::~WeaponHold() = default;

bool WeaponHold::init_(sead::Heap* heap) {
    return OnetimeStopASPlay::init_(heap);
}

void WeaponHold::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
}

void WeaponHold::leave_() {
    OnetimeStopASPlay::leave_();
}

void WeaponHold::loadParams_() {
    OnetimeStopASPlay::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

void WeaponHold::calc_() {
    OnetimeStopASPlay::calc_();
}

}  // namespace uking::action
