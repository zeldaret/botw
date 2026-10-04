#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LevelFlyMoveBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(LevelFlyMoveBase, ksys::act::ai::Action)
public:
    explicit LevelFlyMoveBase(const InitArg& arg);
    ~LevelFlyMoveBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mXZSpeed_s{};
    // static_param at offset 0x28
    const float* mRotSpd_s{};
    // static_param at offset 0x30
    const float* mFinRotate_s{};
    // static_param at offset 0x38
    const float* mHorizontalFinRadius_s{};
    // static_param at offset 0x40
    const float* mVerticalFinLength_s{};
    // static_param at offset 0x48
    const float* mTargetHeightOffset_s{};
    // static_param at offset 0x50
    const float* mRotRatio_s{};
    // static_param at offset 0x58
    const float* mRiseSpeed_s{};
    // static_param at offset 0x60
    const float* mDownSpeed_s{};
    // static_param at offset 0x68
    const float* mCheckStopSpeed_s{};
    // static_param at offset 0x70
    const float* mVibrateMemoryStep_s{};
    // static_param at offset 0x78
    const float* mVibrateCheckFrame_s{};
    // static_param at offset 0x80
    const float* mVibrateStopCheck_s{};
    // static_param at offset 0x88
    const bool* mIsOverRise_s{};
    // static_param at offset 0x90
    const bool* mIsSlowDownNearGoal_s{};
    // dynamic_param at offset 0x98
    sead::Vector3f* mTargetPos_d{};
    // aitree_variable at offset 0xa0
    void* mRefPosVibrateChecker_a{};
};

}  // namespace uking::action
