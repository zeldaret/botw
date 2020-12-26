#include "Game/AI/Action/actionWillBallAction.h"

namespace uking::action {

WillBallAction::WillBallAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WillBallAction::~WillBallAction() = default;

bool WillBallAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WillBallAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WillBallAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void WillBallAction::loadParams_() {
    getStaticParam(&mRotBaseRatio_s, "RotBaseRatio");
    getStaticParam(&mMaxSpeed_s, "MaxSpeed");
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getStaticParam(&mReachRange_s, "ReachRange");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mTiredAngle_s, "TiredAngle");
    getStaticParam(&mIsIgnoreLastSpRot_s, "IsIgnoreLastSpRot");
    getStaticParam(&mIsAddAABBHeight_s, "IsAddAABBHeight");
    getStaticParam(&mIsGround_s, "IsGround");
    getStaticParam(&mAccel_s, "Accel");
}

void WillBallAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
