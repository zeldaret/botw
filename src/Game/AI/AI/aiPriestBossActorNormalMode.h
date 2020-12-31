#pragma once

#include "Game/AI/AI/aiPriestBossMode.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossActorNormalMode : public PriestBossMode {
    SEAD_RTTI_OVERRIDE(PriestBossActorNormalMode, PriestBossMode)
public:
    explicit PriestBossActorNormalMode(const InitArg& arg);
    ~PriestBossActorNormalMode() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x40
    const int* mApproachWarpRate_s{};
    // static_param at offset 0x48
    const float* mApproachStartDistance_s{};
    // static_param at offset 0x50
    const float* mLeaveStartDistance_s{};
    // static_param at offset 0x58
    const float* mLeaveStartTime_s{};
    // static_param at offset 0x60
    const float* mWaitMinTime_s{};
    // static_param at offset 0x68
    const float* mWaitMaxTime_s{};
    // static_param at offset 0x70
    const float* mSecondHalfLifePercent_s{};
    // static_param at offset 0x78
    const float* mFramesRestrictEarthRelease_s{};
    // static_param at offset 0x80
    const float* mWarpPosDistFromPlayer_s{};
    // static_param at offset 0x88
    const float* mStageMarginRateForEarthRelease_s{};
    // static_param at offset 0x90
    const bool* mIsManagedBtlMgr_s{};
    // dynamic_param at offset 0x98
    bool* mFromSyncMode_d{};
    // aitree_variable at offset 0xa0
    int* mEquipWeaponBufIndex_a{};
    // aitree_variable at offset 0xa8
    bool* mReturnFromBananaMode_a{};
};

}  // namespace uking::ai
