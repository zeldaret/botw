#pragma once

#include "Game/AI/AI/aiPriestBossBananaMode.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossCloneBananaMode : public PriestBossBananaMode {
    SEAD_RTTI_OVERRIDE(PriestBossCloneBananaMode, PriestBossBananaMode)
public:
    explicit PriestBossCloneBananaMode(const InitArg& arg);
    ~PriestBossCloneBananaMode() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
