#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkASHoldLegTurn : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkASHoldLegTurn, ksys::act::ai::Action)
public:
    explicit ForkASHoldLegTurn(const InitArg& arg);
    ~ForkASHoldLegTurn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mRotSpeed_s{};
    // static_param at offset 0x28
    const float* mStopSpeedRatio_s{};
    // static_param at offset 0x30
    const float* mStopRotSpeedRatio_s{};
    // static_param at offset 0x38
    const float* mTargetPosNoUpdateArea_s{};
    // static_param at offset 0x40
    const bool* mIsFixBoneWithGround_s{};
    // static_param at offset 0x48
    sead::SafeString mRotBaseBoneName_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
