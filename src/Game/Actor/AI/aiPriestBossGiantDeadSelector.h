#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossGiantDeadSelector : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PriestBossGiantDeadSelector, ksys::act::ai::Ai)
public:
    explicit PriestBossGiantDeadSelector(const InitArg& arg);
    ~PriestBossGiantDeadSelector() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x38
    bool* mPriestBossDownSideASPlaying_a{};
};

}  // namespace uking::ai
