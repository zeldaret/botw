#include "Game/AI/Action/actionWeaponTrueFormEftCtrl.h"

namespace uking::action {

WeaponTrueFormEftCtrl::WeaponTrueFormEftCtrl(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WeaponTrueFormEftCtrl::~WeaponTrueFormEftCtrl() = default;

bool WeaponTrueFormEftCtrl::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WeaponTrueFormEftCtrl::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WeaponTrueFormEftCtrl::leave_() {
    ksys::act::ai::Action::leave_();
}

void WeaponTrueFormEftCtrl::loadParams_() {
    getStaticParam(&mTransformKey_s, "TransformKey");
    getStaticParam(&mTrueFormKey_s, "TrueFormKey");
}

void WeaponTrueFormEftCtrl::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
