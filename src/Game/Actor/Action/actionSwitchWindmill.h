#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SwitchWindmill : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SwitchWindmill, ksys::act::ai::Action)
public:
    explicit SwitchWindmill(const InitArg& arg);
    ~SwitchWindmill() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // FIXME: remove this
    u8 pad_0x20[0xe0];
    // static_param at offset 0x100
    const float* mSwRadTh_s{};
    // static_param at offset 0x108
    const float* mSwRadAllowance_s{};
    // static_param at offset 0x110
    const float* mRotAccel_s{};
    // static_param at offset 0x118
    const float* mMaxRotSpeed_s{};
    // static_param at offset 0x120
    sead::SafeString mTargetNodeName_s{};
};

}  // namespace uking::action
