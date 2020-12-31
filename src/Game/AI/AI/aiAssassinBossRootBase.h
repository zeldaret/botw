#pragma once

#include "Game/AI/AI/aiEnemyRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AssassinBossRootBase : public EnemyRoot {
    SEAD_RTTI_OVERRIDE(AssassinBossRootBase, EnemyRoot)
public:
    explicit AssassinBossRootBase(const InitArg& arg);
    ~AssassinBossRootBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x1d8
    const int* mRockBallDamage_s{};
    // static_param at offset 0x1e0
    const float* mChangeModeLifeRatio_s{};
};

}  // namespace uking::ai
