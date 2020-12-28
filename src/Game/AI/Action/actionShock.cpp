#include "Game/AI/Action/actionShock.h"

namespace uking::action {

Shock::Shock(const InitArg& arg) : ksys::act::ai::Action(arg) {}

Shock::~Shock() = default;

void Shock::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void Shock::leave_() {
    ksys::act::ai::Action::leave_();
}

void Shock::loadParams_() {
    getStaticParam(&mHitImpactForce_s, "HitImpactForce");
    getStaticParam(&mVelReduce_s, "VelReduce");
    getStaticParam(&mKnockBackTime_s, "KnockBackTime");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mWeaponDropSpeedXZ_s, "WeaponDropSpeedXZ");
    getStaticParam(&mWeaponDropSpeedY_s, "WeaponDropSpeedY");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mASSlot_s, "ASSlot");
}

void Shock::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
