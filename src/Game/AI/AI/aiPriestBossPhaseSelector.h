#pragma once

#include "Game/AI/AI/aiPriestBossMode.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossPhaseSelector : public PriestBossMode {
    SEAD_RTTI_OVERRIDE(PriestBossPhaseSelector, PriestBossMode)
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
