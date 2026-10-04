#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossMakeClone : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PriestBossMakeClone, ksys::act::ai::Ai)
public:
    explicit PriestBossMakeClone(const InitArg& arg);
    ~PriestBossMakeClone() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mRespawnFrame_s{};
    // static_param at offset 0x40
    const float* mBackStepDistance_s{};
    // aitree_variable at offset 0x48
    void* mPriestBossMetaAIUnit_a{};
};

}  // namespace uking::ai
