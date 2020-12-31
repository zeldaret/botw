#pragma once

#include "Game/AI/AI/aiAttackGrave.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossAttackGrave : public AttackGrave {
    SEAD_RTTI_OVERRIDE(PriestBossAttackGrave, AttackGrave)
public:
    explicit PriestBossAttackGrave(const InitArg& arg);
    ~PriestBossAttackGrave() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
