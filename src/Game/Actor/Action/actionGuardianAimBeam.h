#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GuardianAimBeam : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(GuardianAimBeam, ksys::act::ai::Action)
public:
    explicit GuardianAimBeam(const InitArg& arg);
    ~GuardianAimBeam() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mTargetOffset_s{};
    // static_param at offset 0x28
    const float* mTargetOffsetY_s{};
    // static_param at offset 0x30
    const float* mFluctuationRange_s{};
    // static_param at offset 0x38
    const float* mFluctuationTime_s{};
    // static_param at offset 0x40
    const float* mFluctuationSpan_s{};
    // static_param at offset 0x48
    sead::SafeString mNodeName_s{};
    // static_param at offset 0x58
    const sead::Vector3f* mNodeOffset_s{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
