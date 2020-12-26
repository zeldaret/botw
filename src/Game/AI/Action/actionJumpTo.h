#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class JumpTo : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(JumpTo, ksys::act::ai::Action)
public:
    explicit JumpTo(const InitArg& arg);
    ~JumpTo() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mMaxSpeed_s{};
    // static_param at offset 0x28
    const float* mJumpHeight_s{};
    // static_param at offset 0x30
    const float* mJumpGravity_s{};
    // static_param at offset 0x38
    const float* mPosReduceRatioOnGround_s{};
    // static_param at offset 0x40
    const float* mRotReduceRatioOnGround_s{};
    // static_param at offset 0x48
    const float* mInWaterDepth_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
