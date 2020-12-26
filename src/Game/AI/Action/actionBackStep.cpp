#include "Game/AI/Action/actionBackStep.h"

namespace uking::action {

BackStep::BackStep(const InitArg& arg) : BackStepBase(arg) {}

BackStep::~BackStep() = default;

bool BackStep::init_(sead::Heap* heap) {
    return BackStepBase::init_(heap);
}

void BackStep::enter_(ksys::act::ai::InlineParamPack* params) {
    BackStepBase::enter_(params);
}

void BackStep::leave_() {
    BackStepBase::leave_();
}

void BackStep::loadParams_() {
    BackStepToTarget::loadParams_();
    getStaticParam(&mJumpDist_s, "JumpDist");
}

void BackStep::calc_() {
    BackStepBase::calc_();
}

}  // namespace uking::action
