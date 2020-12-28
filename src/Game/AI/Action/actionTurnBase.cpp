#include "Game/AI/Action/actionTurnBase.h"

namespace uking::action {

TurnBase::TurnBase(const InitArg& arg) : ActionEx(arg) {}

TurnBase::~TurnBase() = default;

void TurnBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void TurnBase::leave_() {
    ActionEx::leave_();
}

void TurnBase::loadParams_() {
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mBaseRotRatio_s, "BaseRotRatio");
    getStaticParam(&mIsFollowGround_s, "IsFollowGround");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mRotMinSpeedRatio_s, "RotMinSpeedRatio");
}

void TurnBase::calc_() {
    ActionEx::calc_();
}

}  // namespace uking::action
