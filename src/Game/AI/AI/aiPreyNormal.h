#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PreyNormal : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PreyNormal, ksys::act::ai::Ai)
public:
    explicit PreyNormal(const InitArg& arg);
    ~PreyNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mChangeBattleStateRadius_s{};
    // static_param at offset 0x40
    const float* mCounterAttackRadius_s{};
    // static_param at offset 0x48
    const float* mCounterAttackRate_s{};
    // static_param at offset 0x50
    const float* mAddCautionLevelVal_s{};
    // static_param at offset 0x58
    const float* mAutoReduceCautionLevelVal_s{};
    // static_param at offset 0x60
    const float* mLimitOverReduceCautionLevelVal_s{};
    // static_param at offset 0x68
    const float* mAwnRangeScaleWhenAttention_s{};
    // static_param at offset 0x70
    const float* mTargetLostTime_s{};
    // static_param at offset 0x78
    const float* mAllowRoarRadius_s{};
    // static_param at offset 0x80
    const float* mEscapeWaterFlowLimit_s{};
    // static_param at offset 0x88
    const float* mNewFoodAddTime_s{};
    // static_param at offset 0x90
    const bool* mIsUseEscapeState_s{};
    // static_param at offset 0x98
    const bool* mIsPositiveAttacker_s{};
    // static_param at offset 0xa0
    const bool* mIsSearchTarget_s{};
    // static_param at offset 0xa8
    const bool* mIsEmitForceEscapeSignal_s{};
    // static_param at offset 0xb0
    const bool* mIsReceivedForceEscapeSignal_s{};
    // static_param at offset 0xb8
    const bool* mIsCheckSandStorm_s{};
    // map_unit_param at offset 0xc0
    const bool* mIsLocatorCreate_m{};
    // map_unit_param at offset 0xc8
    const bool* mEnableNoEntryAreaCheck_m{};
};

}  // namespace uking::ai
