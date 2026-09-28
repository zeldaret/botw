#include "Game/Actor/Action/actionKnockBackHitImpactForce.h"

namespace uking::action {

KnockBackHitImpactForce::KnockBackHitImpactForce(const InitArg& arg) : ActionEx(arg) {}

KnockBackHitImpactForce::~KnockBackHitImpactForce() = default;

void KnockBackHitImpactForce::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void KnockBackHitImpactForce::loadParams_() {
    getStaticParam(&mHitImpactForceSmallSwordS_s, "HitImpactForceSmallSwordS");
    getStaticParam(&mHitImpactForceSmallSwordL_s, "HitImpactForceSmallSwordL");
    getStaticParam(&mHitImpactForceLargeSwordS_s, "HitImpactForceLargeSwordS");
    getStaticParam(&mHitImpactForceLargeSwordL_s, "HitImpactForceLargeSwordL");
    getStaticParam(&mHitImpactForceSpearS_s, "HitImpactForceSpearS");
    getStaticParam(&mHitImpactForceSpearL_s, "HitImpactForceSpearL");
    getStaticParam(&mVelReduce_s, "VelReduce");
    getStaticParam(&mHighSpeedY_s, "HighSpeedY");
    getStaticParam(&mVelReduceY_s, "VelReduceY");
}

void KnockBackHitImpactForce::calc_() {
    ActionEx::calc_();
}

}  // namespace uking::action
