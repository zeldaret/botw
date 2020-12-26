#include "Game/AI/Action/actionGrabLeftTurn.h"

namespace uking::action {

GrabLeftTurn::GrabLeftTurn(const InitArg& arg) : TurnBase(arg) {}

GrabLeftTurn::~GrabLeftTurn() = default;

bool GrabLeftTurn::init_(sead::Heap* heap) {
    return TurnBase::init_(heap);
}

void GrabLeftTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    TurnBase::enter_(params);
}

void GrabLeftTurn::leave_() {
    TurnBase::leave_();
}

void GrabLeftTurn::loadParams_() {
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mBaseRotRatio_s, "BaseRotRatio");
    getStaticParam(&mIsFollowGround_s, "IsFollowGround");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mRotMinSpeedRatio_s, "RotMinSpeedRatio");
}

void GrabLeftTurn::calc_() {
    TurnBase::calc_();
}

}  // namespace uking::action
