#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseRiddenByPlayer : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(HorseRiddenByPlayer, ksys::act::ai::Action)
public:
    explicit HorseRiddenByPlayer(const InitArg& arg);
    ~HorseRiddenByPlayer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mMaxAcceleration_s{};
    // static_param at offset 0x28
    const float* mSlideToCurveRatio_s{};
    // static_param at offset 0x30
    const float* mTiredFramesAfterGearTop_s{};
    // static_param at offset 0x38
    const float* mCheckFramesSootheAtFirstRun_s{};
    // static_param at offset 0x40
    const float* mCheckFramesSootheAfterRun_s{};
    // static_param at offset 0x48
    const float* mCheckFramesSootheAfterGearTop_s{};
    // static_param at offset 0x50
    const float* mCheckFramesSootheAfterJump_s{};
    // static_param at offset 0x58
    const float* mCheckFramesSootheAfterResist_s{};
    // static_param at offset 0x60
    const float* mCheckFramesAccInputAfterResist_s{};
    // static_param at offset 0x68
    const float* mMinFramesForRunSoothe_s{};
    // static_param at offset 0x70
    const float* mFamiliarityEffectDelayFrames_s{};
    // static_param at offset 0x78
    const float* mChargeRecoveryFrames_s{};
    // static_param at offset 0x80
    const float* mChargeRecoveryFramesSecondly_s{};
    // static_param at offset 0x88
    const float* mChargePenaltyFrames_s{};
    // static_param at offset 0x90
    const float* mSwitchFramesByTemperature_s{};
    // static_param at offset 0x98
    const float* mForwardBentFramesAtGearTop_s{};
    // static_param at offset 0xa0
    const float* mFallHeightForPlayingAS_s{};
    // static_param at offset 0xa8
    const float* mFallHeightForPlayingASInRunning_s{};
    // static_param at offset 0xb0
    const float* mFallRayCastLength_s{};
    // static_param at offset 0xb8
    const float* mFamiliarityThresholdOfRailTrace_s{};
    // static_param at offset 0xc0
    const float* mFamiliarityThresholdOfResist_s{};
    // static_param at offset 0xc8
    const float* mFamiliarityThresholdOfWaitAngry_s{};
    // static_param at offset 0xd0
    const float* mResistGearDownProbability_s{};
    // static_param at offset 0xd8
    const float* mResistChangeSteeringProbability_s{};
    // static_param at offset 0xe0
    const float* mResistChangeSteeringMinFrames_s{};
    // static_param at offset 0xe8
    const float* mResistChangeSteeringMaxFrames_s{};
    // static_param at offset 0xf0
    const float* mResistChangeSteeringInputRange_s{};
    // static_param at offset 0xf8
    const float* mFramesPlayAngryWhileResist_s{};
    // static_param at offset 0x100
    const float* mDelayFramesResistGearDown_s{};
    // static_param at offset 0x108
    const float* mDelayFramesResistChangeSteering_s{};
    // static_param at offset 0x110
    const float* mStressDecBySoothe_s{};
    // static_param at offset 0x118
    const float* mStressIncByImpossibleAcc_s{};
    // static_param at offset 0x120
    const float* mStressIncByEnemy_s{};
    // static_param at offset 0x128
    const float* mStressIncByDamage_s{};
};

}  // namespace uking::action
