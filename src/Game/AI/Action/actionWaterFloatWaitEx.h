#pragma once

#include "Game/AI/Action/actionWaterFloatWait.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WaterFloatWaitEx : public WaterFloatWait {
    SEAD_RTTI_OVERRIDE(WaterFloatWaitEx, WaterFloatWait)
public:
    explicit WaterFloatWaitEx(const InitArg& arg);
    ~WaterFloatWaitEx() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xb0
    const float* mAdditionalPosReduceRatio_s{};
    // static_param at offset 0xb8
    const float* mAdditionalAngleReduceRatio_s{};
    // static_param at offset 0xc0
    const float* mAdditionalVelocityMax_s{};
    // static_param at offset 0xc8
    const float* mWaterEffectSpeedRate_s{};
};

}  // namespace uking::action
