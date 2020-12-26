#include "Game/AI/Action/actionSmallDamage.h"

namespace uking::action {

SmallDamage::SmallDamage(const InitArg& arg) : SmallDamageBase(arg) {}

SmallDamage::~SmallDamage() = default;

bool SmallDamage::init_(sead::Heap* heap) {
    return SmallDamageBase::init_(heap);
}

void SmallDamage::enter_(ksys::act::ai::InlineParamPack* params) {
    SmallDamageBase::enter_(params);
}

void SmallDamage::leave_() {
    SmallDamageBase::leave_();
}

void SmallDamage::loadParams_() {
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

void SmallDamage::calc_() {
    SmallDamageBase::calc_();
}

}  // namespace uking::action
