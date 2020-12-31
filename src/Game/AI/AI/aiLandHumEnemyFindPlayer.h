#pragma once

#include "Game/AI/AI/aiEnemyBaseFindPlayer.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LandHumEnemyFindPlayer : public EnemyBaseFindPlayer {
    SEAD_RTTI_OVERRIDE(LandHumEnemyFindPlayer, EnemyBaseFindPlayer)
public:
    explicit LandHumEnemyFindPlayer(const InitArg& arg);
    ~LandHumEnemyFindPlayer() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x140
    const int* mThrowWeaponPer_s{};
    // static_param at offset 0x148
    const int* mNoChemSearchWpIdx_s{};
    // static_param at offset 0x150
    const float* mExplosivesAvoidDist_s{};
    // static_param at offset 0x158
    const float* mExplosivesAvoidSpeed_s{};
    // static_param at offset 0x160
    const float* mExplosivesAvoidAng_s{};
    // static_param at offset 0x168
    const float* mChemicalSearchDist_s{};
    // static_param at offset 0x170
    const float* mNoSearchDist_s{};
    // static_param at offset 0x178
    const float* mVoltage_s{};
    // static_param at offset 0x180
    const float* mChemicalActionDist_s{};
    // static_param at offset 0x188
    const float* mThrowWeaponDist_s{};
    // static_param at offset 0x190
    const float* mNoBurnWaterDepth_s{};
    // static_param at offset 0x198
    const float* mNearScaffoldDist_s{};
    // static_param at offset 0x1a0
    const float* mClimbVmin_s{};
    // static_param at offset 0x1a8
    const float* mClimbVmax_s{};
    // static_param at offset 0x1b0
    const float* mClimbHmax_s{};
};

}  // namespace uking::ai
