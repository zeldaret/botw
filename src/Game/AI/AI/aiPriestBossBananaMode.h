#pragma once

#include "Game/AI/AI/aiPriestBossMode.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossBananaMode : public PriestBossMode {
    SEAD_RTTI_OVERRIDE(PriestBossBananaMode, PriestBossMode)
public:
    explicit PriestBossBananaMode(const InitArg& arg);
    ~PriestBossBananaMode() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x80
    const int* mHealAmount_s{};
    // static_param at offset 0x88
    const float* mTimeUpFrames_s{};
    // aitree_variable at offset 0x90
    bool* mReturnFromBananaMode_a{};
};

}  // namespace uking::ai
