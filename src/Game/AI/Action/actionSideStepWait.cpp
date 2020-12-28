#include "Game/AI/Action/actionSideStepWait.h"

namespace uking::action {

SideStepWait::SideStepWait(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SideStepWait::~SideStepWait() = default;

void SideStepWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SideStepWait::leave_() {
    ksys::act::ai::Action::leave_();
}

void SideStepWait::loadParams_() {
    getStaticParam(&mFirstStepDist_s, "FirstStepDist");
    getStaticParam(&mSecondStepDist_s, "SecondStepDist");
    getStaticParam(&mThirdStepDist_s, "ThirdStepDist");
    getStaticParam(&mFourthStepDist_s, "FourthStepDist");
    getStaticParam(&mGravity_s, "Gravity");
    getStaticParam(&mFirstStepHeight_s, "FirstStepHeight");
    getStaticParam(&mSecondStepHeight_s, "SecondStepHeight");
    getStaticParam(&mThirdStepHeight_s, "ThirdStepHeight");
    getStaticParam(&mFourthStepHeight_s, "FourthStepHeight");
    getStaticParam(&mStopSpeedRatio_s, "StopSpeedRatio");
    getStaticParam(&mStopRotSpeedRatio_s, "StopRotSpeedRatio");
}

void SideStepWait::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
