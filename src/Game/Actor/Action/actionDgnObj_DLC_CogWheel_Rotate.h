#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DgnObj_DLC_CogWheel_Rotate : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DgnObj_DLC_CogWheel_Rotate, ksys::act::ai::Action)
public:
    explicit DgnObj_DLC_CogWheel_Rotate(const InitArg& arg);
    ~DgnObj_DLC_CogWheel_Rotate() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mTargetAngularDisplPerSec_s{};
    // dynamic_param at offset 0x28
    bool* mIsRegisteredFrame_d{};
    // map_unit_param at offset 0x30
    const float* mGearRatio_m{};
    // map_unit_param at offset 0x38
    const bool* mIsClockWiseRotation_m{};
    // aitree_variable at offset 0x40
    float* mRotationOffset_a{};
};

}  // namespace uking::action
