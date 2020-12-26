#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NpcSwimMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NpcSwimMove, ksys::act::ai::Action)
public:
    explicit NpcSwimMove(const InitArg& arg);
    ~NpcSwimMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mRotRadPerSec_s{};
    // static_param at offset 0x28
    const float* mWallHitTime_s{};
    // static_param at offset 0x30
    const float* mFinRadius_s{};
    // static_param at offset 0x38
    const float* mFinHeight_s{};
    // static_param at offset 0x40
    const float* mFinRotate_s{};
    // static_param at offset 0x48
    const float* mInWaterDepth_s{};
    // static_param at offset 0x50
    const float* mFloatDepth_s{};
    // static_param at offset 0x58
    const float* mFloatRadius_s{};
    // static_param at offset 0x60
    const float* mFloatCycleTime_s{};
    // static_param at offset 0x68
    const float* mChangeDepthSpeed_s{};
    // static_param at offset 0x70
    const bool* mIsClampRotVel_s{};
    // static_param at offset 0x78
    sead::SafeString mASName_s{};
    // static_param at offset 0x88
    const sead::Vector3f* mAddCalcStickX_s{};
    // dynamic_param at offset 0x90
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
