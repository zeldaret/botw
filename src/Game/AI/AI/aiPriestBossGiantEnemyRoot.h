#pragma once

#include "Game/AI/AI/aiPriestBossActorEnemyRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossGiantEnemyRoot : public PriestBossActorEnemyRoot {
    SEAD_RTTI_OVERRIDE(PriestBossGiantEnemyRoot, PriestBossActorEnemyRoot)
public:
    explicit PriestBossGiantEnemyRoot(const InitArg& arg);
    ~PriestBossGiantEnemyRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x230
    const int* mInvalidateIronBallDamageFrame_s{};
    // aitree_variable at offset 0x238
    bool* mPriestBossDownSideASPlaying_a{};
    // aitree_variable at offset 0x240
    void* mPriestBossMetaAIUnit_a{};
};

}  // namespace uking::ai
