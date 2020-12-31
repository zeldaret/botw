#pragma once

#include "Game/AI/AI/aiPriestBossPhase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossPhaseFirst : public PriestBossPhase {
    SEAD_RTTI_OVERRIDE(PriestBossPhaseFirst, PriestBossPhase)
public:
    explicit PriestBossPhaseFirst(const InitArg& arg);
    ~PriestBossPhaseFirst() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
