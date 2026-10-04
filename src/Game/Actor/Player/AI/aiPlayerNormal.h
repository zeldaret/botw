#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PlayerNormal : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PlayerNormal, ksys::act::ai::Ai)
public:
    explicit PlayerNormal(const InitArg& arg);
    ~PlayerNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // FIXME: remove this
    u8 pad_0x38[0x30];
    // static_param at offset 0x68
    const float* mEquipNoiseValue_s{};
    // static_param at offset 0x70
    const float* mAttackNoiseValue_s{};
    // static_param at offset 0x78
    const float* mArrowReadyNoiseValue_s{};
    // static_param at offset 0x80
    const float* mParashawlInvalidHeight_s{};
    // static_param at offset 0x88
    const float* mParashawlInvalidHeightSurfing_s{};
    // static_param at offset 0x90
    const float* mForceSlipSpeed_s{};
    // static_param at offset 0x98
    const float* mDoForbidTime_s{};
    // static_param at offset 0xa0
    const float* mNoRideJumpDiffY_s{};
    // static_param at offset 0xa8
    const float* mDashUpEnableSpeed_s{};
    // static_param at offset 0xb0
    const float* mEnergyPerChargeLv_s{};
    // static_param at offset 0xb8
    const float* mEnergyChargeStart_s{};
    // static_param at offset 0xc0
    const float* mWallSlipEnableSpeed_s{};
    // static_param at offset 0xc8
    const float* mCutAddSpeedRate_s{};
    // static_param at offset 0xd0
    const float* mCutAddSpeedMax_s{};
    // static_param at offset 0xd8
    const float* mCutAddSpeedDec_s{};
    // static_param at offset 0xe0
    const float* mHorseCallTime_s{};
    // static_param at offset 0xe8
    const float* mSwordSearchAngle_s{};
    // static_param at offset 0xf0
    const float* mDoClimbForbidTime_s{};
    // static_param at offset 0xf8
    const float* mDoClimbForbidAngVel_s{};
    // static_param at offset 0x100
    const float* mInWaterTimeForRagdoll_s{};
    // static_param at offset 0x108
    const float* mToFallHeightForJustRush_s{};
};

}  // namespace uking::ai
