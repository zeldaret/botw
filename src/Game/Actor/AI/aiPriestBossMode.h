#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossMode : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PriestBossMode, ksys::act::ai::Ai)
public:
    explicit PriestBossMode(const InitArg& arg);
    ~PriestBossMode() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x38
    void* mPriestBossMetaAIUnit_a{};
};

}  // namespace uking::ai
