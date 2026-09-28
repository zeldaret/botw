#include "Game/Actor/Action/actionFlyingCharacterFreeFallBase.h"

namespace uking::action {

FlyingCharacterFreeFallBase::FlyingCharacterFreeFallBase(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

FlyingCharacterFreeFallBase::~FlyingCharacterFreeFallBase() = default;

bool FlyingCharacterFreeFallBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void FlyingCharacterFreeFallBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void FlyingCharacterFreeFallBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void FlyingCharacterFreeFallBase::loadParams_() {
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
    getStaticParam(&mIsControlRotation_s, "IsControlRotation");
    getStaticParam(&mIsSetBackLastState_s, "IsSetBackLastState");
}

void FlyingCharacterFreeFallBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
