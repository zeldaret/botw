#pragma once

#include "Game/AI/AI/aiPriestBossActorEnemyRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossShadowCloneEnemyRoot : public PriestBossActorEnemyRoot {
    SEAD_RTTI_OVERRIDE(PriestBossShadowCloneEnemyRoot, PriestBossActorEnemyRoot)
public:
    explicit PriestBossShadowCloneEnemyRoot(const InitArg& arg);
    ~PriestBossShadowCloneEnemyRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
