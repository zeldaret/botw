#include "Game/AI/Action/actionFlyingCharacterFreeFallDie.h"

namespace uking::action {

FlyingCharacterFreeFallDie::FlyingCharacterFreeFallDie(const InitArg& arg)
    : FlyingCharacterReaction(arg) {}

FlyingCharacterFreeFallDie::~FlyingCharacterFreeFallDie() = default;

bool FlyingCharacterFreeFallDie::init_(sead::Heap* heap) {
    return FlyingCharacterReaction::init_(heap);
}

void FlyingCharacterFreeFallDie::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingCharacterReaction::enter_(params);
}

void FlyingCharacterFreeFallDie::leave_() {
    FlyingCharacterReaction::leave_();
}

void FlyingCharacterFreeFallDie::loadParams_() {
    FlyingCharacterReaction::loadParams_();
    getStaticParam(&mPosReduceRatioOnGround_s, "PosReduceRatioOnGround");
    getStaticParam(&mRotReduceRatioOnGround_s, "RotReduceRatioOnGround");
    getStaticParam(&mFallAS_s, "FallAS");
    getStaticParam(&mOnGroundAS_s, "OnGroundAS");
}

void FlyingCharacterFreeFallDie::calc_() {
    FlyingCharacterReaction::calc_();
}

}  // namespace uking::action
