#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkSlipAndStop : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkSlipAndStop, ksys::act::ai::Action)
public:
    explicit ForkSlipAndStop(const InitArg& arg);
    ~ForkSlipAndStop() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mPosReduceRatioForSlip_s{};
    // static_param at offset 0x28
    const float* mAngReduceRatioForSlip_s{};
    // static_param at offset 0x30
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x38
    const float* mAngReduceRatio_s{};
    // static_param at offset 0x40
    const bool* mUseLineCheck_s{};
};

}  // namespace uking::action
