#pragma once

#include "Game/AI/AI/aiPriestBossPhase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossPhaseThird : public PriestBossPhase {
    SEAD_RTTI_OVERRIDE(PriestBossPhaseThird, PriestBossPhase)
public:
    explicit PriestBossPhaseThird(const InitArg& arg);
    ~PriestBossPhaseThird() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x80
    const int* mBreakIronBallCount_s{};
};

}  // namespace uking::ai
