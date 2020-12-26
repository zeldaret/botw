#include "Game/AI/Action/actionSmallDamageBase.h"

namespace uking::action {

SmallDamageBase::SmallDamageBase(const InitArg& arg) : TakeHitImpactForce(arg) {}

SmallDamageBase::~SmallDamageBase() = default;

bool SmallDamageBase::init_(sead::Heap* heap) {
    return TakeHitImpactForce::init_(heap);
}

void SmallDamageBase::enter_(ksys::act::ai::InlineParamPack* params) {
    TakeHitImpactForce::enter_(params);
}

void SmallDamageBase::leave_() {
    TakeHitImpactForce::leave_();
}

void SmallDamageBase::loadParams_() {
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

void SmallDamageBase::calc_() {
    TakeHitImpactForce::calc_();
}

}  // namespace uking::action
