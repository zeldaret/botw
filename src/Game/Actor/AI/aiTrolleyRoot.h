#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TrolleyRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TrolleyRoot, ksys::act::ai::Ai)
public:
    explicit TrolleyRoot(const InitArg& arg);
    ~TrolleyRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mNearGoalDist_s{};
    // static_param at offset 0x40
    const float* mNearGoalLimitSpd_s{};
    // static_param at offset 0x48
    const float* mNearGoalReduceRate_s{};
};

}  // namespace uking::ai
