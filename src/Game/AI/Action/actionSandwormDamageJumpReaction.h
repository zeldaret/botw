#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SandwormDamageJumpReaction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SandwormDamageJumpReaction, ksys::act::ai::Action)
public:
    explicit SandwormDamageJumpReaction(const InitArg& arg);
    ~SandwormDamageJumpReaction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mTargetSandOffset_s{};
    // static_param at offset 0x28
    const float* mSandOffsetSpeed_s{};
    // static_param at offset 0x30
    const float* mJumpHeight_s{};
    // static_param at offset 0x38
    const float* mReduceGravityRate_s{};
    // static_param at offset 0x40
    const float* mReduceRotRate_s{};
    // static_param at offset 0x48
    const bool* mWaitASFinish_s{};
    // static_param at offset 0x50
    const bool* mWaitSandOffset_s{};
    // static_param at offset 0x58
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
