#include "Game/AI/Action/actionDieAnmKnockBack.h"

namespace uking::action {

DieAnmKnockBack::DieAnmKnockBack(const InitArg& arg) : SmallDamageBase(arg) {}

DieAnmKnockBack::~DieAnmKnockBack() = default;

void DieAnmKnockBack::enter_(ksys::act::ai::InlineParamPack* params) {
    SmallDamageBase::enter_(params);
}

void DieAnmKnockBack::leave_() {
    SmallDamageBase::leave_();
}

void DieAnmKnockBack::loadParams_() {
    TakeHitImpactForce::loadParams_();
    getStaticParam(&mWeaponDropSpeedY_s, "WeaponDropSpeedY");
    getStaticParam(&mIsDropWeapon_s, "IsDropWeapon");
    getStaticParam(&mASName_s, "ASName");
}

void DieAnmKnockBack::calc_() {
    SmallDamageBase::calc_();
}

}  // namespace uking::action
