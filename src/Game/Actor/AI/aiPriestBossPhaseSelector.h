#pragma once

#include "Game/Actor/AI/aiPriestBoss.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossPhaseSelector : public PriestBoss {
    SEAD_RTTI_OVERRIDE(PriestBossPhaseSelector, PriestBoss)
public:
    explicit PriestBossPhaseSelector(const InitArg& arg);
    ~PriestBossPhaseSelector() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x40
    const bool* mIsSelectOnlyOnce_s{};
};

}  // namespace uking::ai
