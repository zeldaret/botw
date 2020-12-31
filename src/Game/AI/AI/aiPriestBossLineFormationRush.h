#pragma once

#include "Game/AI/AI/aiPriestBossFormation.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossLineFormationRush : public PriestBossFormation {
    SEAD_RTTI_OVERRIDE(PriestBossLineFormationRush, PriestBossFormation)
public:
    explicit PriestBossLineFormationRush(const InitArg& arg);
    ~PriestBossLineFormationRush() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
