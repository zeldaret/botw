#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class KorokGoalTimerRootAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(KorokGoalTimerRootAI, ksys::act::ai::Ai)
public:
    explicit KorokGoalTimerRootAI(const InitArg& arg);
    ~KorokGoalTimerRootAI() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const float* mGoalCountLimit_m{};
};

}  // namespace uking::ai
