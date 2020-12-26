#include "Game/AI/Action/actionFlyingCharacterDamageBase.h"

namespace uking::action {

FlyingCharacterDamageBase::FlyingCharacterDamageBase(const InitArg& arg)
    : FlyingCharacterReaction(arg) {}

FlyingCharacterDamageBase::~FlyingCharacterDamageBase() = default;

bool FlyingCharacterDamageBase::init_(sead::Heap* heap) {
    return FlyingCharacterReaction::init_(heap);
}

void FlyingCharacterDamageBase::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingCharacterReaction::enter_(params);
}

void FlyingCharacterDamageBase::leave_() {
    FlyingCharacterReaction::leave_();
}

void FlyingCharacterDamageBase::loadParams_() {
    FlyingCharacterReaction::loadParams_();
    getStaticParam(&mHitImpactForceSmallSwordS_s, "HitImpactForceSmallSwordS");
    getStaticParam(&mHitImpactForceSmallSwordL_s, "HitImpactForceSmallSwordL");
    getStaticParam(&mHitImpactForceLargeSwordS_s, "HitImpactForceLargeSwordS");
    getStaticParam(&mHitImpactForceLargeSwordL_s, "HitImpactForceLargeSwordL");
    getStaticParam(&mHitImpactForceSpearS_s, "HitImpactForceSpearS");
    getStaticParam(&mHitImpactForceSpearL_s, "HitImpactForceSpearL");
    getStaticParam(&mRiseSpeed_s, "RiseSpeed");
    getStaticParam(&mLastSpeedRatio_s, "LastSpeedRatio");
    getStaticParam(&mPosReduceRatioOnGround_s, "PosReduceRatioOnGround");
    getStaticParam(&mRotReduceRatioOnGround_s, "RotReduceRatioOnGround");
    getStaticParam(&mIsCheckFallASFinished_s, "IsCheckFallASFinished");
    getStaticParam(&mIsIgnoreSameAS4Fall_s, "IsIgnoreSameAS4Fall");
    getStaticParam(&mIsIgnoreSameAS4OnGround_s, "IsIgnoreSameAS4OnGround");
    getStaticParam(&mFallAS_s, "FallAS");
    getStaticParam(&mOnGroundAS_s, "OnGroundAS");
}

void FlyingCharacterDamageBase::calc_() {
    FlyingCharacterReaction::calc_();
}

}  // namespace uking::action
