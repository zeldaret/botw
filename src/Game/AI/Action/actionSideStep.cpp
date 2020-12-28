#include "Game/AI/Action/actionSideStep.h"

namespace uking::action {

SideStep::SideStep(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SideStep::~SideStep() = default;

void SideStep::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SideStep::leave_() {
    ksys::act::ai::Action::leave_();
}

void SideStep::loadParams_() {
    getStaticParam(&mRotSpeedRatio_s, "RotSpeedRatio");
    getStaticParam(&mStopSpeedRatio_s, "StopSpeedRatio");
    getStaticParam(&mStopRotSpeedRatio_s, "StopRotSpeedRatio");
    getStaticParam(&mGravity_s, "Gravity");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void SideStep::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
