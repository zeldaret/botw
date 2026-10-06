#pragma once

#include "Game/Actor/AI/aiPriestBoss.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossNormalQuickRecover : public PriestBoss {
    SEAD_RTTI_OVERRIDE(PriestBossNormalQuickRecover, PriestBoss)
public:
    explicit PriestBossNormalQuickRecover(const InitArg& arg);
    ~PriestBossNormalQuickRecover() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x40
    bool* mIsFromRagdoll_d{};
};

}  // namespace uking::ai
