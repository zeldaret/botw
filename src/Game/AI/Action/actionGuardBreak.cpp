#include "Game/AI/Action/actionGuardBreak.h"

namespace uking::action {

GuardBreak::GuardBreak(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GuardBreak::~GuardBreak() = default;

bool GuardBreak::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GuardBreak::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GuardBreak::leave_() {
    ksys::act::ai::Action::leave_();
}

void GuardBreak::loadParams_() {
    getStaticParam(&mKnockBackTime_s, "KnockBackTime");
    getStaticParam(&mDropIdx_s, "DropIdx");
    getStaticParam(&mHitImpactForce_s, "HitImpactForce");
    getStaticParam(&mVelReduce_s, "VelReduce");
    getStaticParam(&mWeaponVel_s, "WeaponVel");
    getStaticParam(&mWeaponVelY_s, "WeaponVelY");
}

void GuardBreak::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
