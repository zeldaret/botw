#pragma once

#include "Game/AI/AI/aiEnemyDefaultReaction.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossNormalReaction : public EnemyDefaultReaction {
    SEAD_RTTI_OVERRIDE(PriestBossNormalReaction, EnemyDefaultReaction)
public:
    explicit PriestBossNormalReaction(const InitArg& arg);
    ~PriestBossNormalReaction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x68
    const bool* mIsUseQuickRecover_s{};
    // aitree_variable at offset 0x70
    bool* mPriestBossUrbosasFuryEShock_a{};
    // aitree_variable at offset 0x78
    void* mPriestBossMetaAIUnit_a{};
};

}  // namespace uking::ai
