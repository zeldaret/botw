#include "Game/Actor/Action/actionFlyingCharacterFreeze.h"

namespace uking::action {

FlyingCharacterFreeze::FlyingCharacterFreeze(const InitArg& arg)
    : FlyingCharacterFreeFallBase(arg) {}

bool FlyingCharacterFreeze::init_(sead::Heap* heap) {
    return FlyingCharacterFreeFallBase::init_(heap);
}

void FlyingCharacterFreeze::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingCharacterFreeFallBase::enter_(params);
}

void FlyingCharacterFreeze::leave_() {
    FlyingCharacterFreeFallBase::leave_();
}

void FlyingCharacterFreeze::loadParams_() {
    FlyingCharacterFreeFallBase::loadParams_();
    getStaticParam(&mStopTime_s, "StopTime");
}

void FlyingCharacterFreeze::calc_() {
    FlyingCharacterFreeFallBase::calc_();
}

}  // namespace uking::action
