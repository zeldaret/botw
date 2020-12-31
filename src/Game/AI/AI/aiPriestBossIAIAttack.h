#pragma once

#include "Game/AI/AI/aiIAIAttack.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossIAIAttack : public IAIAttack {
    SEAD_RTTI_OVERRIDE(PriestBossIAIAttack, IAIAttack)
public:
    explicit PriestBossIAIAttack(const InitArg& arg);
    ~PriestBossIAIAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
