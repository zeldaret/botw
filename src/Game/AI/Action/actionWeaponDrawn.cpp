#include "Game/AI/Action/actionWeaponDrawn.h"

namespace uking::action {

WeaponDrawn::WeaponDrawn(const InitArg& arg) : OnetimeStopASPlay(arg) {}

WeaponDrawn::~WeaponDrawn() = default;

bool WeaponDrawn::init_(sead::Heap* heap) {
    return OnetimeStopASPlay::init_(heap);
}

void WeaponDrawn::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
}

void WeaponDrawn::leave_() {
    OnetimeStopASPlay::leave_();
}

void WeaponDrawn::loadParams_() {
    OnetimeStopASPlay::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

void WeaponDrawn::calc_() {
    OnetimeStopASPlay::calc_();
}

}  // namespace uking::action
