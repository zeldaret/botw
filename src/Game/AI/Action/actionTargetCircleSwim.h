#pragma once

#include "Game/AI/Action/actionTargetCircle.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class TargetCircleSwim : public TargetCircle {
    SEAD_RTTI_OVERRIDE(TargetCircleSwim, TargetCircle)
public:
    explicit TargetCircleSwim(const InitArg& arg);
    ~TargetCircleSwim() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x80
    const float* mFloatDepth_s{};
    // static_param at offset 0x88
    const float* mFloatRadius_s{};
    // static_param at offset 0x90
    const float* mFloatCycleTime_s{};
    // static_param at offset 0x98
    const float* mInWaterDepth_s{};
    // static_param at offset 0xa0
    const float* mChangeDepthSpeed_s{};
};

}  // namespace uking::action
