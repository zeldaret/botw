#pragma once

#include "Game/AI/AI/aiPriestBossActorGiantRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossActorGiantFouthRoot : public PriestBossActorGiantRoot {
    SEAD_RTTI_OVERRIDE(PriestBossActorGiantFouthRoot, PriestBossActorGiantRoot)
public:
    explicit PriestBossActorGiantFouthRoot(const InitArg& arg);
    ~PriestBossActorGiantFouthRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xf8
    const float* mStompDistance_s{};
    // static_param at offset 0x100
    const float* mStompInAreaTimer_s{};
    // static_param at offset 0x108
    const bool* mStompAction_s{};
    // static_param at offset 0x110
    const bool* mStompAlwaysChange_s{};
    // aitree_variable at offset 0x118
    void* mPriestBossMetaAIUnit_a{};
};

}  // namespace uking::ai
