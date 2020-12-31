#pragma once

#include "Game/AI/AI/aiPriestBossMode.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossNormalQuickRecover : public PriestBossMode {
    SEAD_RTTI_OVERRIDE(PriestBossNormalQuickRecover, PriestBossMode)
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
