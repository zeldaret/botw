#pragma once

#include "Game/AI/AI/aiEnemyDefaultReaction.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossGiantReaction : public EnemyDefaultReaction {
    SEAD_RTTI_OVERRIDE(PriestBossGiantReaction, EnemyDefaultReaction)
public:
    explicit PriestBossGiantReaction(const InitArg& arg);
    ~PriestBossGiantReaction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x68
    bool* mPriestBossUrbosasFuryEShock_a{};
};

}  // namespace uking::ai
