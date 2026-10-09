#include "Game/Actor/Action/actionWillBallBase.h"

namespace uking::action {

WillBallBase::WillBallBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WillBallBase::~WillBallBase() = default;

bool WillBallBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WillBallBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WillBallBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void WillBallBase::loadParams_() {
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

void WillBallBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
