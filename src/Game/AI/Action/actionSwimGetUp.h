#pragma once

#include "Game/AI/Action/actionGetUp.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SwimGetUp : public GetUp {
    SEAD_RTTI_OVERRIDE(SwimGetUp, GetUp)
public:
    explicit SwimGetUp(const InitArg& arg);
    ~SwimGetUp() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x160
    const float* mInWaterDepth_s{};
    // static_param at offset 0x168
    const float* mFloatDepth_s{};
    // static_param at offset 0x170
    const float* mFloatRadius_s{};
    // static_param at offset 0x178
    const float* mFloatCycleTime_s{};
    // static_param at offset 0x180
    const float* mChangeDepthSpeed_s{};
    // static_param at offset 0x188
    const float* mUnderWaterDepth_s{};
};

}  // namespace uking::action
