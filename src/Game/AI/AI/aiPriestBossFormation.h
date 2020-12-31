#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossFormation : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PriestBossFormation, ksys::act::ai::Ai)
public:
    explicit PriestBossFormation(const InitArg& arg);
    ~PriestBossFormation() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x38
    void* mPriestBossMetaAIUnit_a{};
};

}  // namespace uking::ai
