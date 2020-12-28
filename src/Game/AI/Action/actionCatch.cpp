#include "Game/AI/Action/actionCatch.h"

namespace uking::action {

Catch::Catch(const InitArg& arg) : ActionEx(arg) {}

Catch::~Catch() = default;

void Catch::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void Catch::leave_() {
    ActionEx::leave_();
}

void Catch::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getDynamicParam(&mTargetWeapon_d, "TargetWeapon");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mASName_s, "ASName");
}

void Catch::calc_() {
    ActionEx::calc_();
}

}  // namespace uking::action
