#include "Game/AI/Action/actionGuardTurn.h"

namespace uking::action {

GuardTurn::GuardTurn(const InitArg& arg) : TurnBase(arg) {}

GuardTurn::~GuardTurn() = default;

bool GuardTurn::init_(sead::Heap* heap) {
    return TurnBase::init_(heap);
}

void GuardTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    TurnBase::enter_(params);
}

void GuardTurn::leave_() {
    TurnBase::leave_();
}

void GuardTurn::loadParams_() {
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mBaseRotRatio_s, "BaseRotRatio");
    getStaticParam(&mIsFollowGround_s, "IsFollowGround");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mRotMinSpeedRatio_s, "RotMinSpeedRatio");
}

void GuardTurn::calc_() {
    TurnBase::calc_();
}

}  // namespace uking::action
