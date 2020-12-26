#include "Game/AI/Action/actionFlyingCharacterFreeFall.h"

namespace uking::action {

FlyingCharacterFreeFall::FlyingCharacterFreeFall(const InitArg& arg)
    : FlyingCharacterReaction(arg) {}

FlyingCharacterFreeFall::~FlyingCharacterFreeFall() = default;

bool FlyingCharacterFreeFall::init_(sead::Heap* heap) {
    return FlyingCharacterReaction::init_(heap);
}

void FlyingCharacterFreeFall::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingCharacterReaction::enter_(params);
}

void FlyingCharacterFreeFall::leave_() {
    FlyingCharacterReaction::leave_();
}

void FlyingCharacterFreeFall::loadParams_() {
    FlyingCharacterReaction::loadParams_();
}

void FlyingCharacterFreeFall::calc_() {
    FlyingCharacterReaction::calc_();
}

}  // namespace uking::action
