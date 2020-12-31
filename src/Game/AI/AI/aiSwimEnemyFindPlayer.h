#pragma once

#include "Game/AI/AI/aiEnemyBaseFindPlayer.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SwimEnemyFindPlayer : public EnemyBaseFindPlayer {
    SEAD_RTTI_OVERRIDE(SwimEnemyFindPlayer, EnemyBaseFindPlayer)
public:
    explicit SwimEnemyFindPlayer(const InitArg& arg);
    ~SwimEnemyFindPlayer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x140
    const bool* mIsAbleToLand_s{};
    // static_param at offset 0x150
    const float* mNearScaffoldDist_s{};
    // static_param at offset 0x158
    const float* mClimbVmin_s{};
    // static_param at offset 0x160
    const float* mClimbVmax_s{};
    // static_param at offset 0x168
    const float* mClimbHmax_s{};
};

}  // namespace uking::ai
