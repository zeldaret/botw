#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SideStepWait : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SideStepWait, ksys::act::ai::Action)
public:
    explicit SideStepWait(const InitArg& arg);
    ~SideStepWait() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mFirstStepDist_s{};
    // static_param at offset 0x28
    const float* mSecondStepDist_s{};
    // static_param at offset 0x30
    const float* mThirdStepDist_s{};
    // static_param at offset 0x38
    const float* mFourthStepDist_s{};
    // static_param at offset 0x40
    const float* mGravity_s{};
    // static_param at offset 0x48
    const float* mFirstStepHeight_s{};
    // static_param at offset 0x50
    const float* mSecondStepHeight_s{};
    // static_param at offset 0x58
    const float* mThirdStepHeight_s{};
    // static_param at offset 0x60
    const float* mFourthStepHeight_s{};
    // static_param at offset 0x68
    const float* mStopSpeedRatio_s{};
    // static_param at offset 0x70
    const float* mStopRotSpeedRatio_s{};
};

}  // namespace uking::action
