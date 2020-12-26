#include "Game/AI/Action/actionTurn.h"

namespace uking::action {

Turn::Turn(const InitArg& arg) : TurnBase(arg) {}

Turn::~Turn() = default;

bool Turn::init_(sead::Heap* heap) {
    return TurnBase::init_(heap);
}

void Turn::enter_(ksys::act::ai::InlineParamPack* params) {
    TurnBase::enter_(params);
}

void Turn::leave_() {
    TurnBase::leave_();
}

void Turn::loadParams_() {
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mBaseRotRatio_s, "BaseRotRatio");
    getStaticParam(&mIsFollowGround_s, "IsFollowGround");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mRotMinSpeedRatio_s, "RotMinSpeedRatio");
}

void Turn::calc_() {
    TurnBase::calc_();
}

}  // namespace uking::action
