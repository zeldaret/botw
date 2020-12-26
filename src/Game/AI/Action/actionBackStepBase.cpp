#include "Game/AI/Action/actionBackStepBase.h"

namespace uking::action {

BackStepBase::BackStepBase(const InitArg& arg) : BackStepToTarget(arg) {}

BackStepBase::~BackStepBase() = default;

bool BackStepBase::init_(sead::Heap* heap) {
    return BackStepToTarget::init_(heap);
}

void BackStepBase::enter_(ksys::act::ai::InlineParamPack* params) {
    BackStepToTarget::enter_(params);
}

void BackStepBase::leave_() {
    BackStepToTarget::leave_();
}

void BackStepBase::loadParams_() {
    BackStepToTarget::loadParams_();
    getStaticParam(&mJumpDist_s, "JumpDist");
}

void BackStepBase::calc_() {
    BackStepToTarget::calc_();
}

}  // namespace uking::action
