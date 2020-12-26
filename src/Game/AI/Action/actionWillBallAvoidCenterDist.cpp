#include "Game/AI/Action/actionWillBallAvoidCenterDist.h"

namespace uking::action {

WillBallAvoidCenterDist::WillBallAvoidCenterDist(const InitArg& arg) : WillBallAction(arg) {}

WillBallAvoidCenterDist::~WillBallAvoidCenterDist() = default;

bool WillBallAvoidCenterDist::init_(sead::Heap* heap) {
    return WillBallAction::init_(heap);
}

void WillBallAvoidCenterDist::enter_(ksys::act::ai::InlineParamPack* params) {
    WillBallAction::enter_(params);
}

void WillBallAvoidCenterDist::leave_() {
    WillBallAction::leave_();
}

void WillBallAvoidCenterDist::loadParams_() {
    WillBallAction::loadParams_();
    getStaticParam(&mDist_s, "Dist");
    getStaticParam(&mMaxDist_s, "MaxDist");
    getStaticParam(&mMiddleDist_s, "MiddleDist");
    getDynamicParam(&mCenterPos_d, "CenterPos");
}

void WillBallAvoidCenterDist::calc_() {
    WillBallAction::calc_();
}

}  // namespace uking::action
