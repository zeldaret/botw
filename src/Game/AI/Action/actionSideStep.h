#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SideStep : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SideStep, ksys::act::ai::Action)
public:
    explicit SideStep(const InitArg& arg);
    ~SideStep() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mRotSpeedRatio_s{};
    // static_param at offset 0x28
    const float* mStopSpeedRatio_s{};
    // static_param at offset 0x30
    const float* mStopRotSpeedRatio_s{};
    // static_param at offset 0x38
    const float* mGravity_s{};
    // static_param at offset 0x40
    const float* mJumpHeight_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
