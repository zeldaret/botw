#include "Game/AI/Action/actionFlyingCharacterFreeze.h"

namespace uking::action {

FlyingCharacterFreeze::FlyingCharacterFreeze(const InitArg& arg) : FlyingCharacterReaction(arg) {}

bool FlyingCharacterFreeze::init_(sead::Heap* heap) {
    return FlyingCharacterReaction::init_(heap);
}

void FlyingCharacterFreeze::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingCharacterReaction::enter_(params);
}

void FlyingCharacterFreeze::leave_() {
    FlyingCharacterReaction::leave_();
}

void FlyingCharacterFreeze::loadParams_() {
    FlyingCharacterReaction::loadParams_();
    getStaticParam(&mStopTime_s, "StopTime");
}

void FlyingCharacterFreeze::calc_() {
    FlyingCharacterReaction::calc_();
}

}  // namespace uking::action
