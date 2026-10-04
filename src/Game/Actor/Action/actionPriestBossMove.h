#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PriestBossMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(PriestBossMove, ksys::act::ai::Action)
public:
    explicit PriestBossMove(const InitArg& arg);
    ~PriestBossMove() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mWeaponIdx_s{};
    // static_param at offset 0x28
    const int* mWallHitLimitTime_s{};
    // static_param at offset 0x30
    const int* mMoveAngCliffLimitTime_s{};
    // static_param at offset 0x38
    const int* mNotMoveLimitTime_s{};
    // static_param at offset 0x40
    const float* mSpeed_s{};
    // static_param at offset 0x48
    const float* mAccRatio_s{};
    // static_param at offset 0x50
    const float* mInitRotSpd_s{};
    // static_param at offset 0x58
    const float* mAccRotSpd_s{};
    // static_param at offset 0x60
    const float* mMaxRotSpd_s{};
    // static_param at offset 0x68
    const float* mFinRadius_s{};
    // static_param at offset 0x70
    const float* mFinRotate_s{};
    // static_param at offset 0x78
    const float* mFrontCliffDistance_s{};
    // static_param at offset 0x80
    const float* mFrontCliffAngle_s{};
    // static_param at offset 0x88
    const float* mJumpUpSpeedReduceRatio_s{};
    // static_param at offset 0x90
    const float* mNotMoveDistanceThreshold_s{};
    // static_param at offset 0x98
    const bool* mFollowGround_s{};
    // static_param at offset 0xa0
    const bool* mIgnoreLastCurve_s{};
    // static_param at offset 0xa8
    const bool* mIgnoreDecelerationFrontCliff_s{};
    // static_param at offset 0xb0
    const bool* mIgnoreMoveDirCoHit_s{};
    // static_param at offset 0xb8
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0xc8
    sead::Vector3f* mMoveTargetPos_d{};
};

}  // namespace uking::action
