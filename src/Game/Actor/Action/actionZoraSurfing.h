#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ZoraSurfing : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ZoraSurfing, ksys::act::ai::Action)
public:
    explicit ZoraSurfing(const InitArg& arg);
    ~ZoraSurfing() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // FIXME: remove this
    u8 pad_0x20[0x90];
    // static_param at offset 0xb0
    const float* mRotRadPerSec_s{};
    // static_param at offset 0xb8
    const float* mWallHitTime_s{};
    // static_param at offset 0xc0
    const float* mFinRadius_s{};
    // static_param at offset 0xc8
    const float* mFinHeight_s{};
    // static_param at offset 0xd0
    const float* mFinRotate_s{};
    // static_param at offset 0xd8
    const float* mInWaterDepth_s{};
    // static_param at offset 0xe0
    const float* mFloatDepth_s{};
    // static_param at offset 0xe8
    const float* mFloatRadius_s{};
    // static_param at offset 0xf0
    const float* mFloatCycleTime_s{};
    // static_param at offset 0xf8
    const float* mChangeDepthSpeed_s{};
    // static_param at offset 0x100
    const float* mOnRailDistance_s{};
    // static_param at offset 0x108
    const float* mFarDistance_s{};
    // static_param at offset 0x110
    const float* mSpeed_s{};
    // static_param at offset 0x118
    const bool* mIsClampRotVel_s{};
    // static_param at offset 0x120
    sead::SafeString mASName_s{};
    // static_param at offset 0x130
    sead::SafeString mASNameJump_s{};
    // static_param at offset 0x140
    const sead::Vector3f* mAddCalcStickX_s{};
    // dynamic_param at offset 0x148
    sead::SafeString mUniqueName_d{};
};

}  // namespace uking::action
