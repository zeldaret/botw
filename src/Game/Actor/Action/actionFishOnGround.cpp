#include "Game/Actor/Action/actionFishOnGround.h"

namespace uking::action {

FishOnGround::FishOnGround(const InitArg& arg) : StopBase(arg) {}

FishOnGround::~FishOnGround() = default;

bool FishOnGround::init_(sead::Heap* heap) {
    return StopBase::init_(heap);
}

void FishOnGround::enter_(ksys::act::ai::InlineParamPack* params) {
    StopBase::enter_(params);
}

void FishOnGround::leave_() {
    StopBase::leave_();
}

void FishOnGround::loadParams_() {
    StopBase::loadParams_();
    getStaticParam(&mASKey_s, "ASKey");
}

void FishOnGround::calc_() {
    StopBase::calc_();
}

}  // namespace uking::action
