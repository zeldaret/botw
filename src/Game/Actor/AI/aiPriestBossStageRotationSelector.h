#pragma once

#include "Game/Actor/AI/aiPriestBoss.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossStageRotationSelector : public PriestBoss {
    SEAD_RTTI_OVERRIDE(PriestBossStageRotationSelector, PriestBoss)
public:
    explicit PriestBossStageRotationSelector(const InitArg& arg);
    ~PriestBossStageRotationSelector() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
