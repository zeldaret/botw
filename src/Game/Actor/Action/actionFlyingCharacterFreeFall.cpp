#include "Game/Actor/Action/actionFlyingCharacterFreeFall.h"

namespace uking::action {

FlyingCharacterFreeFall::FlyingCharacterFreeFall(const InitArg& arg)
    : FlyingCharacterFreeFallBase(arg) {}

FlyingCharacterFreeFall::~FlyingCharacterFreeFall() = default;

bool FlyingCharacterFreeFall::init_(sead::Heap* heap) {
    return FlyingCharacterFreeFallBase::init_(heap);
}

void FlyingCharacterFreeFall::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingCharacterFreeFallBase::enter_(params);
}

void FlyingCharacterFreeFall::leave_() {
    FlyingCharacterFreeFallBase::leave_();
}

void FlyingCharacterFreeFall::loadParams_() {
    FlyingCharacterFreeFallBase::loadParams_();
}

void FlyingCharacterFreeFall::calc_() {
    FlyingCharacterFreeFallBase::calc_();
}

}  // namespace uking::action
