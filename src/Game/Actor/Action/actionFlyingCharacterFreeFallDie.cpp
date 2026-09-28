#include "Game/Actor/Action/actionFlyingCharacterFreeFallDie.h"

namespace uking::action {

FlyingCharacterFreeFallDie::FlyingCharacterFreeFallDie(const InitArg& arg)
    : FlyingCharacterFreeFallBase(arg) {}

FlyingCharacterFreeFallDie::~FlyingCharacterFreeFallDie() = default;

bool FlyingCharacterFreeFallDie::init_(sead::Heap* heap) {
    return FlyingCharacterFreeFallBase::init_(heap);
}

void FlyingCharacterFreeFallDie::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingCharacterFreeFallBase::enter_(params);
}

void FlyingCharacterFreeFallDie::leave_() {
    FlyingCharacterFreeFallBase::leave_();
}

void FlyingCharacterFreeFallDie::loadParams_() {
    FlyingCharacterFreeFallBase::loadParams_();
    getStaticParam(&mPosReduceRatioOnGround_s, "PosReduceRatioOnGround");
    getStaticParam(&mRotReduceRatioOnGround_s, "RotReduceRatioOnGround");
    getStaticParam(&mFallAS_s, "FallAS");
    getStaticParam(&mOnGroundAS_s, "OnGroundAS");
}

void FlyingCharacterFreeFallDie::calc_() {
    FlyingCharacterFreeFallBase::calc_();
}

}  // namespace uking::action
