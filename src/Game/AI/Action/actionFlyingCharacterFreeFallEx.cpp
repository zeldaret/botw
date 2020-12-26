#include "Game/AI/Action/actionFlyingCharacterFreeFallEx.h"

namespace uking::action {

FlyingCharacterFreeFallEx::FlyingCharacterFreeFallEx(const InitArg& arg)
    : FlyingCharacterFreeFall(arg) {}

FlyingCharacterFreeFallEx::~FlyingCharacterFreeFallEx() = default;

bool FlyingCharacterFreeFallEx::init_(sead::Heap* heap) {
    return FlyingCharacterFreeFall::init_(heap);
}

void FlyingCharacterFreeFallEx::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingCharacterFreeFall::enter_(params);
}

void FlyingCharacterFreeFallEx::leave_() {
    FlyingCharacterFreeFall::leave_();
}

void FlyingCharacterFreeFallEx::loadParams_() {
    FlyingCharacterFreeFall::loadParams_();
    getStaticParam(&mGravityScaleRate_s, "GravityScaleRate");
}

void FlyingCharacterFreeFallEx::calc_() {
    FlyingCharacterFreeFall::calc_();
}

}  // namespace uking::action
