#pragma once

#include "Game/AI/AI/aiPriestBossMode.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossStageRotationSelector : public PriestBossMode {
    SEAD_RTTI_OVERRIDE(PriestBossStageRotationSelector, PriestBossMode)
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
