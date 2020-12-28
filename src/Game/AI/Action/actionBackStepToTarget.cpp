#include "Game/AI/Action/actionBackStepToTarget.h"

namespace uking::action {

BackStepToTarget::BackStepToTarget(const InitArg& arg) : ActionEx(arg) {}

BackStepToTarget::~BackStepToTarget() = default;

void BackStepToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void BackStepToTarget::leave_() {
    ActionEx::leave_();
}

void BackStepToTarget::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mStopSpeedRatio_s, "StopSpeedRatio");
    getStaticParam(&mStopRotSpeedRatio_s, "StopRotSpeedRatio");
    getStaticParam(&mJumpGravity_s, "JumpGravity");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mRotRatio_s, "RotRatio");
    getStaticParam(&mCheckRotEvent_s, "CheckRotEvent");
}

void BackStepToTarget::calc_() {
    ActionEx::calc_();
}

}  // namespace uking::action
