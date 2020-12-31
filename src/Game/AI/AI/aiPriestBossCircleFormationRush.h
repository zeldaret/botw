#pragma once

#include "Game/AI/AI/aiPriestBossFormation.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossCircleFormationRush : public PriestBossFormation {
    SEAD_RTTI_OVERRIDE(PriestBossCircleFormationRush, PriestBossFormation)
public:
    explicit PriestBossCircleFormationRush(const InitArg& arg);
    ~PriestBossCircleFormationRush() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x80
    const float* mHomingAttackTime_s{};
};

}  // namespace uking::ai
