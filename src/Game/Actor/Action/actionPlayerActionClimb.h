#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerActionClimb : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(PlayerActionClimb, ksys::act::ai::Action)
public:
    explicit PlayerActionClimb(const InitArg& arg);
    ~PlayerActionClimb() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // FIXME: remove this
    u8 pad_0x20[0x1c8];
    // static_param at offset 0x1e8
    const int* mLockingAfterJumpCnt_s{};
    // static_param at offset 0x1f0
    const int* mChargeJumpLevel1Frame_s{};
    // static_param at offset 0x1f8
    const int* mChageJumpLevel2Frame_s{};
    // static_param at offset 0x200
    const float* mRayCastOffsetY_s{};
    // static_param at offset 0x208
    const float* mEndGroundAngle_s{};
    // static_param at offset 0x210
    const float* mBodyFixedOffset_s{};
    // static_param at offset 0x218
    const float* mRayCastLength_s{};
    // static_param at offset 0x220
    const float* mDashAnmSpdRate_s{};
    // static_param at offset 0x228
    const float* mFlickThresholdMin_s{};
    // static_param at offset 0x230
    const float* mFlickThresholdMax_s{};
    // static_param at offset 0x238
    const float* mFlickWaitToOverMaxTime_s{};
    // static_param at offset 0x240
    const float* mFlickOverMaxToReturnTime_s{};
    // static_param at offset 0x248
    const float* mStaminaDownAlways_s{};
    // static_param at offset 0x250
    const float* mStaminaDownTriggerJump_s{};
    // static_param at offset 0x258
    const float* mStaminaDownWait_s{};
    // static_param at offset 0x260
    const float* mForceStartMoveVelYMin_s{};
    // static_param at offset 0x268
    const float* mChargeJumpScaleMin_s{};
    // static_param at offset 0x270
    const float* mChargeJumpScaleMax_s{};
    // static_param at offset 0x278
    const float* mStaminaDownScaleInRain_s{};
    // static_param at offset 0x280
    const float* mStaminaScaleTriggerJumpLv1_s{};
    // static_param at offset 0x288
    const float* mStaminaScaleTriggerJumpLv2_s{};
    // static_param at offset 0x290
    const float* mStaminaScaleTriggerJumpLv3_s{};
    // static_param at offset 0x298
    const float* mJumpScaleWhenLitteleStamina_s{};
    // static_param at offset 0x2a0
    const float* mNoiseMaxSpeedMove_s{};
    // static_param at offset 0x2a8
    const float* mNoiseMaxValueMove_s{};
    // static_param at offset 0x2b0
    const float* mNoiseMaxValueJump_s{};
    // static_param at offset 0x2b8
    const float* mFallLimitWallAngle_s{};
    // static_param at offset 0x2c0
    const float* mStaminaRateMovingUp_s{};
    // static_param at offset 0x2c8
    const float* mStaminaRateMovingSide_s{};
    // static_param at offset 0x2d0
    const float* mStaminaRateMovingDown_s{};
    // static_param at offset 0x2d8
    const float* mStaminaRateSlopeCenter_s{};
    // static_param at offset 0x2e0
    const float* mStaminaRateSlopeMin_s{};
    // static_param at offset 0x2e8
    const float* mStaminaRateSlopeMax_s{};
    // static_param at offset 0x2f0
    const float* mBodyDiffLengthMaxNormal_s{};
    // static_param at offset 0x2f8
    const float* mBodyDiffLengthMaxJump_s{};
    // static_param at offset 0x300
    const float* mEndWaitRate_s{};
    // static_param at offset 0x308
    const float* mBaseCountSlipInRain_s{};
    // static_param at offset 0x310
    const float* mRandomCountSlipInRain_s{};
    // static_param at offset 0x318
    const float* mBaseSpeedSlipInRain_s{};
    // static_param at offset 0x320
    const float* mRandomSpeedSlipInRain_s{};
    // static_param at offset 0x328
    const float* mDownStaminaSlipInRain_s{};
    // static_param at offset 0x330
    const float* mOcclusionCheckLength_s{};
    // static_param at offset 0x338
    const float* mStaminaDownAlwaysMaxSpeed_s{};
    // dynamic_param at offset 0x340
    bool* mEnableStartAnm_d{};
    // dynamic_param at offset 0x348
    bool* mEnableClimbDown_d{};
    // dynamic_param at offset 0x350
    bool* mFromParashawl_d{};
};

}  // namespace uking::action
