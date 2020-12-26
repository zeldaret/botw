#include "Game/AI/Action/actionTakeHitImpactForce.h"

namespace uking::action {

TakeHitImpactForce::TakeHitImpactForce(const InitArg& arg) : ActionEx(arg) {}

TakeHitImpactForce::~TakeHitImpactForce() = default;

bool TakeHitImpactForce::init_(sead::Heap* heap) {
    return ActionEx::init_(heap);
}

void TakeHitImpactForce::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void TakeHitImpactForce::leave_() {
    ActionEx::leave_();
}

void TakeHitImpactForce::loadParams_() {
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

void TakeHitImpactForce::calc_() {
    ActionEx::calc_();
}

}  // namespace uking::action
