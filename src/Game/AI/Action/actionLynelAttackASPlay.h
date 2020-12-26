#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LynelAttackASPlay : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(LynelAttackASPlay, ksys::act::ai::Action)
public:
    explicit LynelAttackASPlay(const InitArg& arg);
    ~LynelAttackASPlay() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mWeaponIdx_s{};
    // static_param at offset 0x28
    const int* mEndState_s{};
    // static_param at offset 0x30
    const int* mChangeableTiming_s{};
    // static_param at offset 0x38
    const float* mRotSpeed_s{};
    // static_param at offset 0x40
    const float* mSpeed_s{};
    // static_param at offset 0x48
    const float* mTransAccRatio_s{};
    // static_param at offset 0x50
    const float* mRotAccRatio_s{};
    // static_param at offset 0x58
    const float* mRange_s{};
    // static_param at offset 0x60
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x68
    const float* mRotReduceRatio_s{};
    // static_param at offset 0x70
    const float* mJumpUpSpeedReduceRatio_s{};
    // static_param at offset 0x78
    const bool* mIsIgnoreSame_s{};
    // static_param at offset 0x80
    const bool* mUseAnimeDriven_s{};
    // static_param at offset 0x88
    const bool* mIsCheckNavMesh_s{};
    // static_param at offset 0x90
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0xa0
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
