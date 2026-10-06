#include "Game/Actor/Action/actionFlyingCharacterBlownOff.h"

namespace uking::action {

FlyingCharacterBlownOff::FlyingCharacterBlownOff(const InitArg& arg)
    : FlyingCharacterFreeFallBase(arg) {}

FlyingCharacterBlownOff::~FlyingCharacterBlownOff() = default;

bool FlyingCharacterBlownOff::init_(sead::Heap* heap) {
    return FlyingCharacterFreeFallBase::init_(heap);
}

void FlyingCharacterBlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingCharacterFreeFallBase::enter_(params);
}

void FlyingCharacterBlownOff::leave_() {
    FlyingCharacterFreeFallBase::leave_();
}

void FlyingCharacterBlownOff::loadParams_() {
    FlyingCharacterFreeFallBase::loadParams_();
    getStaticParam(&mPosReduceRatioOnGround_s, "PosReduceRatioOnGround");
    getStaticParam(&mRotReduceRatioOnGround_s, "RotReduceRatioOnGround");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRiseSpeed_s, "RiseSpeed");
    getStaticParam(&mFallAS_s, "FallAS");
    getStaticParam(&mOnGroundAS_s, "OnGroundAS");
}

void FlyingCharacterBlownOff::calc_() {
    FlyingCharacterFreeFallBase::calc_();
}

}  // namespace uking::action
