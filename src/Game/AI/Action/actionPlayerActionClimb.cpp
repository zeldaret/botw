#include "Game/AI/Action/actionPlayerActionClimb.h"

namespace uking::action {

PlayerActionClimb::PlayerActionClimb(const InitArg& arg) : ksys::act::ai::Action(arg) {}

PlayerActionClimb::~PlayerActionClimb() = default;

bool PlayerActionClimb::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PlayerActionClimb::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void PlayerActionClimb::leave_() {
    ksys::act::ai::Action::leave_();
}

void PlayerActionClimb::loadParams_() {
    getStaticParam(&mLockingAfterJumpCnt_s, "LockingAfterJumpCnt");
    getStaticParam(&mChargeJumpLevel1Frame_s, "ChargeJumpLevel1Frame");
    getStaticParam(&mChageJumpLevel2Frame_s, "ChageJumpLevel2Frame");
    getStaticParam(&mRayCastOffsetY_s, "RayCastOffsetY");
    getStaticParam(&mEndGroundAngle_s, "EndGroundAngle");
    getStaticParam(&mBodyFixedOffset_s, "BodyFixedOffset");
    getStaticParam(&mRayCastLength_s, "RayCastLength");
    getStaticParam(&mDashAnmSpdRate_s, "DashAnmSpdRate");
    getStaticParam(&mFlickThresholdMin_s, "FlickThresholdMin");
    getStaticParam(&mFlickThresholdMax_s, "FlickThresholdMax");
    getStaticParam(&mFlickWaitToOverMaxTime_s, "FlickWaitToOverMaxTime");
    getStaticParam(&mFlickOverMaxToReturnTime_s, "FlickOverMaxToReturnTime");
    getStaticParam(&mStaminaDownAlways_s, "StaminaDownAlways");
    getStaticParam(&mStaminaDownTriggerJump_s, "StaminaDownTriggerJump");
    getStaticParam(&mStaminaDownWait_s, "StaminaDownWait");
    getStaticParam(&mForceStartMoveVelYMin_s, "ForceStartMoveVelYMin");
    getStaticParam(&mChargeJumpScaleMin_s, "ChargeJumpScaleMin");
    getStaticParam(&mChargeJumpScaleMax_s, "ChargeJumpScaleMax");
    getStaticParam(&mStaminaDownScaleInRain_s, "StaminaDownScaleInRain");
    getStaticParam(&mStaminaScaleTriggerJumpLv1_s, "StaminaScaleTriggerJumpLv1");
    getStaticParam(&mStaminaScaleTriggerJumpLv2_s, "StaminaScaleTriggerJumpLv2");
    getStaticParam(&mStaminaScaleTriggerJumpLv3_s, "StaminaScaleTriggerJumpLv3");
    getStaticParam(&mJumpScaleWhenLitteleStamina_s, "JumpScaleWhenLitteleStamina");
    getStaticParam(&mNoiseMaxSpeedMove_s, "NoiseMaxSpeedMove");
    getStaticParam(&mNoiseMaxValueMove_s, "NoiseMaxValueMove");
    getStaticParam(&mNoiseMaxValueJump_s, "NoiseMaxValueJump");
    getStaticParam(&mFallLimitWallAngle_s, "FallLimitWallAngle");
    getStaticParam(&mStaminaRateMovingUp_s, "StaminaRateMovingUp");
    getStaticParam(&mStaminaRateMovingSide_s, "StaminaRateMovingSide");
    getStaticParam(&mStaminaRateMovingDown_s, "StaminaRateMovingDown");
    getStaticParam(&mStaminaRateSlopeCenter_s, "StaminaRateSlopeCenter");
    getStaticParam(&mStaminaRateSlopeMin_s, "StaminaRateSlopeMin");
    getStaticParam(&mStaminaRateSlopeMax_s, "StaminaRateSlopeMax");
    getStaticParam(&mBodyDiffLengthMaxNormal_s, "BodyDiffLengthMaxNormal");
    getStaticParam(&mBodyDiffLengthMaxJump_s, "BodyDiffLengthMaxJump");
    getStaticParam(&mEndWaitRate_s, "EndWaitRate");
    getStaticParam(&mBaseCountSlipInRain_s, "BaseCountSlipInRain");
    getStaticParam(&mRandomCountSlipInRain_s, "RandomCountSlipInRain");
    getStaticParam(&mBaseSpeedSlipInRain_s, "BaseSpeedSlipInRain");
    getStaticParam(&mRandomSpeedSlipInRain_s, "RandomSpeedSlipInRain");
    getStaticParam(&mDownStaminaSlipInRain_s, "DownStaminaSlipInRain");
    getStaticParam(&mOcclusionCheckLength_s, "OcclusionCheckLength");
    getStaticParam(&mStaminaDownAlwaysMaxSpeed_s, "StaminaDownAlwaysMaxSpeed");
    getDynamicParam(&mEnableStartAnm_d, "EnableStartAnm");
    getDynamicParam(&mEnableClimbDown_d, "EnableClimbDown");
    getDynamicParam(&mFromParashawl_d, "FromParashawl");
}

void PlayerActionClimb::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
