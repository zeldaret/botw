#include "Game/AI/Action/actionGrabRightTurn.h"

namespace uking::action {

GrabRightTurn::GrabRightTurn(const InitArg& arg) : TurnBase(arg) {}

GrabRightTurn::~GrabRightTurn() = default;

bool GrabRightTurn::init_(sead::Heap* heap) {
    return TurnBase::init_(heap);
}

void GrabRightTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    TurnBase::enter_(params);
}

void GrabRightTurn::leave_() {
    TurnBase::leave_();
}

void GrabRightTurn::loadParams_() {
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mBaseRotRatio_s, "BaseRotRatio");
    getStaticParam(&mIsFollowGround_s, "IsFollowGround");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mRotMinSpeedRatio_s, "RotMinSpeedRatio");
}

void GrabRightTurn::calc_() {
    TurnBase::calc_();
}

}  // namespace uking::action
