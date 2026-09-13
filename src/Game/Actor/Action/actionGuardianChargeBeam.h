#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GuardianChargeBeam : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(GuardianChargeBeam, ksys::act::ai::Action)
public:
    explicit GuardianChargeBeam(const InitArg& arg);
    ~GuardianChargeBeam() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mTime_s{};
    // static_param at offset 0x28
    const float* mTimeRand_s{};
    // static_param at offset 0x30
    const float* mChargeRadius_s{};
    // static_param at offset 0x38
    const sead::Vector3f* mColor_s{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
