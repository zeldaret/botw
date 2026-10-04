#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WaterUpDownAnmDrivenMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(WaterUpDownAnmDrivenMove, ksys::act::ai::Action)
public:
    explicit WaterUpDownAnmDrivenMove(const InitArg& arg);
    ~WaterUpDownAnmDrivenMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mInWaterDepth_s{};
    // static_param at offset 0x28
    const float* mTargetDepth_s{};
    // static_param at offset 0x30
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x38
    const float* mRotReduceRatio_s{};
    // static_param at offset 0x40
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
