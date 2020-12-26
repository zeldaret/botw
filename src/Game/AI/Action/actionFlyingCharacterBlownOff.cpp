#include "Game/AI/Action/actionFlyingCharacterBlownOff.h"

namespace uking::action {

FlyingCharacterBlownOff::FlyingCharacterBlownOff(const InitArg& arg)
    : FlyingCharacterReaction(arg) {}

FlyingCharacterBlownOff::~FlyingCharacterBlownOff() = default;

bool FlyingCharacterBlownOff::init_(sead::Heap* heap) {
    return FlyingCharacterReaction::init_(heap);
}

void FlyingCharacterBlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingCharacterReaction::enter_(params);
}

void FlyingCharacterBlownOff::leave_() {
    FlyingCharacterReaction::leave_();
}

void FlyingCharacterBlownOff::loadParams_() {
    FlyingCharacterReaction::loadParams_();
    getStaticParam(&mPosReduceRatioOnGround_s, "PosReduceRatioOnGround");
    getStaticParam(&mRotReduceRatioOnGround_s, "RotReduceRatioOnGround");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRiseSpeed_s, "RiseSpeed");
    getStaticParam(&mFallAS_s, "FallAS");
    getStaticParam(&mOnGroundAS_s, "OnGroundAS");
}

void FlyingCharacterBlownOff::calc_() {
    FlyingCharacterReaction::calc_();
}

}  // namespace uking::action
