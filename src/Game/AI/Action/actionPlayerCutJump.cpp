#include "Game/AI/Action/actionPlayerCutJump.h"

namespace uking::action {

PlayerCutJump::PlayerCutJump(const InitArg& arg) : PlayerAction(arg) {}

void PlayerCutJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerCutJump::leave_() {
    PlayerAction::leave_();
}

void PlayerCutJump::loadParams_() {
    getStaticParam(&mAttackRatioNSword_s, "AttackRatioNSword");
    getStaticParam(&mAttackRatioLSword_s, "AttackRatioLSword");
    getStaticParam(&mAttackRatioSpear_s, "AttackRatioSpear");
    getStaticParam(&mCutJumpSpeedF_s, "CutJumpSpeedF");
    getStaticParam(&mCutJumpHeight_s, "CutJumpHeight");
    getStaticParam(&mCutJumpShortSpeedF_s, "CutJumpShortSpeedF");
    getStaticParam(&mCutJumpShortHeight_s, "CutJumpShortHeight");
    getStaticParam(&mCutJumpSpeedFLSword_s, "CutJumpSpeedFLSword");
    getStaticParam(&mAimDistOffset_s, "AimDistOffset");
    getStaticParam(&mSwingFrameBeforeGround_s, "SwingFrameBeforeGround");
    getStaticParam(&mFallSpAttackHeight_s, "FallSpAttackHeight");
    getStaticParam(&mFallSpAttackRadiusMin_s, "FallSpAttackRadiusMin");
    getStaticParam(&mFallSpAttackRadiusMax_s, "FallSpAttackRadiusMax");
    getStaticParam(&mFallSpAttackRadiusAdd_s, "FallSpAttackRadiusAdd");
    getStaticParam(&mFallSpAttackRadiusAddLSword_s, "FallSpAttackRadiusAddLSword");
    getStaticParam(&mFallSpAttackCheckUnderDist_s, "FallSpAttackCheckUnderDist");
    getStaticParam(&mFallSpLargeAttackRadius_s, "FallSpLargeAttackRadius");
    getStaticParam(&mRumbleType_s, "RumbleType");
    getStaticParam(&mRumblePowerMin_s, "RumblePowerMin");
    getStaticParam(&mRumblePowerMax_s, "RumblePowerMax");
    getStaticParam(&mParashawlInvalidTime_s, "ParashawlInvalidTime");
}

void PlayerCutJump::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
