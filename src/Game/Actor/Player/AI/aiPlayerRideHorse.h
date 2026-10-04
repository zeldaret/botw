#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PlayerRideHorse : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PlayerRideHorse, ksys::act::ai::Ai)
public:
    explicit PlayerRideHorse(const InitArg& arg);
    ~PlayerRideHorse() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mLynelRodeoCutNum_s{};
    // static_param at offset 0x40
    const float* mDoForbidTime_s{};
    // static_param at offset 0x48
    const float* mThrowPowerY_s{};
    // static_param at offset 0x50
    const float* mThrowPowerF_s{};
    // static_param at offset 0x58
    const float* mBackDismountSpeed_s{};
    // static_param at offset 0x60
    const float* mWaistAngleApplyRateFoward_s{};
    // static_param at offset 0x68
    const float* mWaistAngleApplyRateBack_s{};
    // static_param at offset 0x70
    const float* mMoveNoise_s{};
    // static_param at offset 0x78
    const float* mSwordAttackNoise_s{};
    // static_param at offset 0x80
    const float* mAimAngleAddApplyAngle_s{};
    // static_param at offset 0x88
    const float* mAimAngleAdd_s{};
    // static_param at offset 0x90
    const float* mAimAngleAddApplySpeed_s{};
    // static_param at offset 0x98
    const float* mLowerAngleWaitTime_s{};
    // dynamic_param at offset 0xa0
    bool* mHasToPlayRidingOnAS_d{};
};

}  // namespace uking::ai
