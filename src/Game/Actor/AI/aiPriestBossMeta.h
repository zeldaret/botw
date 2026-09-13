#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossMeta : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PriestBossMeta, ksys::act::ai::Ai)
public:
    explicit PriestBossMeta(const InitArg& arg);
    ~PriestBossMeta() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x38
    int* mMetaAILife_a{};
    // aitree_variable at offset 0x40
    int* mMetaAIMaxLife_a{};
    // aitree_variable at offset 0x48
    void* mPriestBossMetaAIUnit_a{};
};

}  // namespace uking::ai
