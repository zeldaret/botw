#include "Game/AI/Action/actionTakeoffFromCeilLookTarget.h"

namespace uking::action {

TakeoffFromCeilLookTarget::TakeoffFromCeilLookTarget(const InitArg& arg)
    : TakeoffFromCeilLook(arg) {}

TakeoffFromCeilLookTarget::~TakeoffFromCeilLookTarget() = default;

bool TakeoffFromCeilLookTarget::init_(sead::Heap* heap) {
    return TakeoffFromCeilLook::init_(heap);
}

void TakeoffFromCeilLookTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    TakeoffFromCeilLook::enter_(params);
}

void TakeoffFromCeilLookTarget::leave_() {
    TakeoffFromCeilLook::leave_();
}

void TakeoffFromCeilLookTarget::loadParams_() {
    TakeoffFromCeilLook::loadParams_();
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void TakeoffFromCeilLookTarget::calc_() {
    TakeoffFromCeilLook::calc_();
}

}  // namespace uking::action
