#include "Game/AI/Action/actionPriestBossMove.h"

namespace uking::action {

PriestBossMove::PriestBossMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

PriestBossMove::~PriestBossMove() = default;

void PriestBossMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void PriestBossMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void PriestBossMove::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mWallHitLimitTime_s, "WallHitLimitTime");
    getStaticParam(&mMoveAngCliffLimitTime_s, "MoveAngCliffLimitTime");
    getStaticParam(&mNotMoveLimitTime_s, "NotMoveLimitTime");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mAccRatio_s, "AccRatio");
    getStaticParam(&mInitRotSpd_s, "InitRotSpd");
    getStaticParam(&mAccRotSpd_s, "AccRotSpd");
    getStaticParam(&mMaxRotSpd_s, "MaxRotSpd");
    getStaticParam(&mFinRadius_s, "FinRadius");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mFrontCliffDistance_s, "FrontCliffDistance");
    getStaticParam(&mFrontCliffAngle_s, "FrontCliffAngle");
    getStaticParam(&mJumpUpSpeedReduceRatio_s, "JumpUpSpeedReduceRatio");
    getStaticParam(&mNotMoveDistanceThreshold_s, "NotMoveDistanceThreshold");
    getStaticParam(&mFollowGround_s, "FollowGround");
    getStaticParam(&mIgnoreLastCurve_s, "IgnoreLastCurve");
    getStaticParam(&mIgnoreDecelerationFrontCliff_s, "IgnoreDecelerationFrontCliff");
    getStaticParam(&mIgnoreMoveDirCoHit_s, "IgnoreMoveDirCoHit");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mMoveTargetPos_d, "MoveTargetPos");
}

void PriestBossMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
