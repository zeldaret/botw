#pragma once

#include "Game/AI/AI/aiPriestBossPhase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossPhaseFinish : public PriestBossPhase {
    SEAD_RTTI_OVERRIDE(PriestBossPhaseFinish, PriestBossPhase)
public:
    explicit PriestBossPhaseFinish(const InitArg& arg);
    ~PriestBossPhaseFinish() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x80
    const float* mStartDemoDelayFrames_s{};
    // map_unit_param at offset 0x88
    const int* mPriestBossStartPhase_m{};
};

}  // namespace uking::ai
