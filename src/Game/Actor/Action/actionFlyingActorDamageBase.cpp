#include "Game/Actor/Action/actionFlyingActorDamageBase.h"

namespace uking::action {

FlyingActorDamageBase::FlyingActorDamageBase(const InitArg& arg)
    : FlyingCharacterFreeFallBase(arg) {}

FlyingActorDamageBase::~FlyingActorDamageBase() = default;

bool FlyingActorDamageBase::init_(sead::Heap* heap) {
    return FlyingCharacterFreeFallBase::init_(heap);
}

void FlyingActorDamageBase::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingCharacterFreeFallBase::enter_(params);
}

void FlyingActorDamageBase::leave_() {
    FlyingCharacterFreeFallBase::leave_();
}

void FlyingActorDamageBase::loadParams_() {
    FlyingCharacterFreeFallBase::loadParams_();
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

void FlyingActorDamageBase::calc_() {
    FlyingCharacterFreeFallBase::calc_();
}

}  // namespace uking::action
