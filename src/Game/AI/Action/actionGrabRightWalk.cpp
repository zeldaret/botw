#include "Game/AI/Action/actionGrabRightWalk.h"

namespace uking::action {

GrabRightWalk::GrabRightWalk(const InitArg& arg) : MoveBase(arg) {}

GrabRightWalk::~GrabRightWalk() = default;

bool GrabRightWalk::init_(sead::Heap* heap) {
    return MoveBase::init_(heap);
}

void GrabRightWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveBase::enter_(params);
}

void GrabRightWalk::leave_() {
    MoveBase::leave_();
}

void GrabRightWalk::loadParams_() {
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

void GrabRightWalk::calc_() {
    MoveBase::calc_();
}

}  // namespace uking::action
