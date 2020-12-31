#pragma once

#include "Game/AI/AI/aiPriestBossPhase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossPhaseSecond : public PriestBossPhase {
    SEAD_RTTI_OVERRIDE(PriestBossPhaseSecond, PriestBossPhase)
public:
    explicit PriestBossPhaseSecond(const InitArg& arg);
    ~PriestBossPhaseSecond() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x80
    const int* mModeChangeLife_s{};
    // static_param at offset 0x88
    const int* mSimAtkMax_s{};
    // static_param at offset 0x90
    const int* mBowEquipMax_s{};
    // static_param at offset 0x98
    const int* mSyncAtkMax_s{};
    // static_param at offset 0xa0
    const float* mModeChangeBlockTime_s{};
    // static_param at offset 0xa8
    const float* mRespawnSpan_s{};
    // static_param at offset 0xb0
    const float* mRespawnBaseSpace_s{};
    // static_param at offset 0xb8
    const float* mRespawnBaseMoveTime_s{};
    // static_param at offset 0xc0
    const float* mRespawnBaseInterval_s{};
    // static_param at offset 0xc8
    const float* mCircleFormRange_s{};
    // static_param at offset 0xd0
    const float* mCircleFormRushWait_s{};
    // static_param at offset 0xd8
    const float* mCircleFormRushInterval_s{};
    // static_param at offset 0xe0
    const float* mCircleFormShootWait_s{};
    // static_param at offset 0xe8
    const float* mCircleFormShootInterval_s{};
    // static_param at offset 0xf0
    const float* mLineFormDistFromPlayer_s{};
    // static_param at offset 0xf8
    const float* mLineFormSpace_s{};
    // static_param at offset 0x100
    const float* mLineFormRushWait_s{};
    // static_param at offset 0x108
    const float* mLineFormRushInterval_s{};
    // static_param at offset 0x110
    const float* mLineFormFallWait_s{};
    // static_param at offset 0x118
    const float* mLineFormFallInterval_s{};
    // map_unit_param at offset 0x120
    const int* mPriestBossStartPhase_m{};
};

}  // namespace uking::ai
