#pragma once

#include "Game/AI/AI/aiPriestBossMeta.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossPhase : public PriestBossMeta {
    SEAD_RTTI_OVERRIDE(PriestBossPhase, PriestBossMeta)
public:
    explicit PriestBossPhase(const InitArg& arg);
    ~PriestBossPhase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x50
    const float* mPercentLifeTransition_s{};
    // static_param at offset 0x58
    const float* mPercentLifePrevious_s{};
};

}  // namespace uking::ai
