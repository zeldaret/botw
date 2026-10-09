#include "Game/Actor/Action/actionWillBallAvoidCenterDist.h"

namespace uking::action {

WillBallAvoidCenterDist::WillBallAvoidCenterDist(const InitArg& arg) : WillBallBase(arg) {}

WillBallAvoidCenterDist::~WillBallAvoidCenterDist() = default;

bool WillBallAvoidCenterDist::init_(sead::Heap* heap) {
    return WillBallBase::init_(heap);
}

void WillBallAvoidCenterDist::enter_(ksys::act::ai::InlineParamPack* params) {
    WillBallBase::enter_(params);
}

void WillBallAvoidCenterDist::leave_() {
    WillBallBase::leave_();
}

void WillBallAvoidCenterDist::loadParams_() {
    WillBallBase::loadParams_();
    getStaticParam(&mDist_s, "Dist");
    getStaticParam(&mMaxDist_s, "MaxDist");
    getStaticParam(&mMiddleDist_s, "MiddleDist");
    getDynamicParam(&mCenterPos_d, "CenterPos");
}

void WillBallAvoidCenterDist::calc_() {
    WillBallBase::calc_();
}

}  // namespace uking::action
