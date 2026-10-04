#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SwitchStepSliderConstraint : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SwitchStepSliderConstraint, ksys::act::ai::Action)
public:
    explicit SwitchStepSliderConstraint(const InitArg& arg);
    ~SwitchStepSliderConstraint() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // FIXME: remove this
    u8 pad_0x20[0x8];
    // static_param at offset 0x28
    const int* mTargetIdx_s{};
    // static_param at offset 0x30
    const int* mSeqBankIdx_s{};
    // static_param at offset 0x38
    const float* mImpulse_s{};
    // static_param at offset 0x40
    const float* mMinLimit_s{};
    // static_param at offset 0x48
    const float* mMaxLimit_s{};
    // static_param at offset 0x50
    const float* mSwTh_s{};
    // static_param at offset 0x58
    const float* mFriction_s{};
    // static_param at offset 0x60
    const bool* mIsIgnoreSame_s{};
    // static_param at offset 0x68
    sead::SafeString mOnASName_s{};
    // static_param at offset 0x78
    sead::SafeString mOffASName_s{};
};

}  // namespace uking::action
