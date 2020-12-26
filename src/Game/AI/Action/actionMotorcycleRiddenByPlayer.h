#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class MotorcycleRiddenByPlayer : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(MotorcycleRiddenByPlayer, ksys::act::ai::Action)
public:
    explicit MotorcycleRiddenByPlayer(const InitArg& arg);
    ~MotorcycleRiddenByPlayer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mCrashVelocityThreshold_s{};
    // static_param at offset 0x28
    const float* mRideOnDelayFrames_s{};
    // static_param at offset 0x30
    const float* mFallThresholdForThrowOff_s{};
    // static_param at offset 0x38
    const float* mCrashVelocityDeltaThreshold_s{};
    // static_param at offset 0x40
    const float* mChargeVelocityThreshold_s{};
    // static_param at offset 0x48
    const float* mDriftCutGrassRange_s{};
    // static_param at offset 0x50
    const float* mDriftCutGrassIntensity_s{};
    // static_param at offset 0x58
    const float* mCutLowTreeVelocityThreshold_s{};
    // static_param at offset 0x60
    const float* mCutLowTreeVelocitySize_s{};
    // static_param at offset 0x68
    const float* mTerrorVelocityThreshold1_s{};
    // static_param at offset 0x70
    const float* mTerrorVelocityThreshold2_s{};
    // static_param at offset 0x78
    const float* mTerrorVelocityThreshold3_s{};
    // static_param at offset 0x80
    const float* mTerrorVelocityThreshold4_s{};
    // static_param at offset 0x88
    const float* mTerrorRadius_s{};
    // static_param at offset 0x90
    const float* mTerrorOffsetDistanceSec_s{};
    // static_param at offset 0x98
    const float* mForbidSpinturnAngleRange_s{};
    // static_param at offset 0xa0
    const float* mPermitManualWheelieAngleRange_s{};
    // static_param at offset 0xa8
    const sead::Vector3f* mAttackChargeBoneOffset_s{};
};

}  // namespace uking::action
