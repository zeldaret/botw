#include "Game/AI/Action/actionLynelAttackASPlay.h"

namespace uking::action {

LynelAttackASPlay::LynelAttackASPlay(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LynelAttackASPlay::~LynelAttackASPlay() = default;

bool LynelAttackASPlay::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LynelAttackASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void LynelAttackASPlay::leave_() {
    ksys::act::ai::Action::leave_();
}

void LynelAttackASPlay::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mEndState_s, "EndState");
    getStaticParam(&mChangeableTiming_s, "ChangeableTiming");
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mTransAccRatio_s, "TransAccRatio");
    getStaticParam(&mRotAccRatio_s, "RotAccRatio");
    getStaticParam(&mRange_s, "Range");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
    getStaticParam(&mJumpUpSpeedReduceRatio_s, "JumpUpSpeedReduceRatio");
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
    getStaticParam(&mUseAnimeDriven_s, "UseAnimeDriven");
    getStaticParam(&mIsCheckNavMesh_s, "IsCheckNavMesh");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void LynelAttackASPlay::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
