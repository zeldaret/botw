#include "Game/AI/Action/actionFlyingCharacterReaction.h"

namespace uking::action {

FlyingCharacterReaction::FlyingCharacterReaction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

FlyingCharacterReaction::~FlyingCharacterReaction() = default;

bool FlyingCharacterReaction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void FlyingCharacterReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void FlyingCharacterReaction::leave_() {
    ksys::act::ai::Action::leave_();
}

void FlyingCharacterReaction::loadParams_() {
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
    getStaticParam(&mIsControlRotation_s, "IsControlRotation");
    getStaticParam(&mIsSetBackLastState_s, "IsSetBackLastState");
}

void FlyingCharacterReaction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
