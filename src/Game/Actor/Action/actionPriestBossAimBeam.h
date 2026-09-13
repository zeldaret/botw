#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PriestBossAimBeam : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(PriestBossAimBeam, ksys::act::ai::Action)
public:
    explicit PriestBossAimBeam(const InitArg& arg);
    ~PriestBossAimBeam() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mAimLockFrame_s{};
    // static_param at offset 0x28
    const float* mTargetOffset_s{};
    // static_param at offset 0x30
    const float* mTargetOffsetY_s{};
    // static_param at offset 0x38
    const float* mFluctuationRange_s{};
    // static_param at offset 0x40
    const float* mFluctuationTime_s{};
    // static_param at offset 0x48
    const float* mFluctuationSpan_s{};
    // static_param at offset 0x50
    const float* mAimMaxLength_s{};
    // static_param at offset 0x58
    const bool* mAimOffToTarget_s{};
    // static_param at offset 0x60
    sead::SafeString mNodeName_s{};
    // static_param at offset 0x70
    const sead::Vector3f* mNodeOffset_s{};
    // dynamic_param at offset 0x78
    sead::Vector3f* mAimTargetPos_d{};
};

}  // namespace uking::action
