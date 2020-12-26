#include "Game/AI/Action/actionGrabLeftWalk.h"

namespace uking::action {

GrabLeftWalk::GrabLeftWalk(const InitArg& arg) : MoveBase(arg) {}

GrabLeftWalk::~GrabLeftWalk() = default;

bool GrabLeftWalk::init_(sead::Heap* heap) {
    return MoveBase::init_(heap);
}

void GrabLeftWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveBase::enter_(params);
}

void GrabLeftWalk::leave_() {
    MoveBase::leave_();
}

void GrabLeftWalk::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mWallHitLimitTime_s, "WallHitLimitTime");
    getStaticParam(&mMoveAngCliffLimitTime_s, "MoveAngCliffLimitTime");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRadius_s, "FinRadius");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mBaseRotRatio_s, "BaseRotRatio");
    getStaticParam(&mAccRatio_s, "AccRatio");
    getStaticParam(&mJumpUpSpeedReduceRatio_s, "JumpUpSpeedReduceRatio");
    getStaticParam(&mFollowGround_s, "FollowGround");
    getStaticParam(&mIgnoreLastCurve_s, "IgnoreLastCurve");
    getStaticParam(&mIgnoreDecelerationFrontCliff_s, "IgnoreDecelerationFrontCliff");
    getStaticParam(&mIgnoreMoveDirCoHit_s, "IgnoreMoveDirCoHit");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void GrabLeftWalk::calc_() {
    MoveBase::calc_();
}

}  // namespace uking::action
