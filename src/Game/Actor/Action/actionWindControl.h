#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WindControl : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(WindControl, ksys::act::ai::Action)
public:
    explicit WindControl(const InitArg& arg);
    ~WindControl() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // FIXME: remove this
    u8 pad_0x20[0xa8];
    // static_param at offset 0xc8
    const float* mRadius_s{};
    // static_param at offset 0xd0
    const float* mMaxSpeed_s{};
    // static_param at offset 0xd8
    const float* mMaxRadSpeed_s{};
    // static_param at offset 0xe0
    const float* mRadAccel_s{};
    // static_param at offset 0xe8
    const float* mTemperature_s{};
    // static_param at offset 0xf0
    const bool* mUseEnvTemperature_s{};
    // static_param at offset 0xf8
    const bool* mIsModelControlOnly_s{};
    // static_param at offset 0x100
    sead::SafeString mTargetNodeName_s{};
};

}  // namespace uking::action
