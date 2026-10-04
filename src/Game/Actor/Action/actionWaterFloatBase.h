#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WaterFloatBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(WaterFloatBase, ksys::act::ai::Action)
public:
    explicit WaterFloatBase(const InitArg& arg);
    ~WaterFloatBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mInWaterDepth_s{};
    // static_param at offset 0x28
    const float* mFloatDepth_s{};
    // static_param at offset 0x30
    const float* mFloatRadius_s{};
    // static_param at offset 0x38
    const float* mFloatCycleTime_s{};
    // static_param at offset 0x40
    const float* mChangeDepthSpeed_s{};
    // static_param at offset 0x48
    const bool* mIsCheckWaterFall_s{};
};

}  // namespace uking::action
