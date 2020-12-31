#pragma once

#include "Game/AI/AI/aiEnemyRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossActorEnemyRoot : public EnemyRoot {
    SEAD_RTTI_OVERRIDE(PriestBossActorEnemyRoot, EnemyRoot)
public:
    explicit PriestBossActorEnemyRoot(const InitArg& arg);
    ~PriestBossActorEnemyRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x1d8
    const bool* mIsReactionOnDead_s{};
    // aitree_variable at offset 0x1e0
    void* mPriestBossMetaAIUnit_a{};
};

}  // namespace uking::ai
