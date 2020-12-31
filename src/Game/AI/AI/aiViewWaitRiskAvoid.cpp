#include "Game/AI/AI/aiViewWaitRiskAvoid.h"

namespace uking::ai {

ViewWaitRiskAvoid::ViewWaitRiskAvoid(const InitArg& arg) : ViewWait(arg) {}

ViewWaitRiskAvoid::~ViewWaitRiskAvoid() = default;

bool ViewWaitRiskAvoid::init_(sead::Heap* heap) {
    return ViewWait::init_(heap);
}

void ViewWaitRiskAvoid::enter_(ksys::act::ai::InlineParamPack* params) {
    ViewWait::enter_(params);
}

void ViewWaitRiskAvoid::leave_() {
    ViewWait::leave_();
}

void ViewWaitRiskAvoid::loadParams_() {
    ViewWait::loadParams_();
    getStaticParam(&mAvoidFrame_s, "AvoidFrame");
    getStaticParam(&mFrontAngle_s, "FrontAngle");
    getStaticParam(&mSpaceAngle_s, "SpaceAngle");
    getStaticParam(&mSpaceDist_s, "SpaceDist");
}

}  // namespace uking::ai
