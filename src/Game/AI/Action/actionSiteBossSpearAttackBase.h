#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossSpearAttackBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SiteBossSpearAttackBase, ksys::act::ai::Action)
public:
    explicit SiteBossSpearAttackBase(const InitArg& arg);
    ~SiteBossSpearAttackBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mAtMinDamage_s{};
    // static_param at offset 0x28
    const int* mAttackPower_s{};
    // static_param at offset 0x30
    const int* mAddAttackPower_s{};
    // static_param at offset 0x38
    const float* mRotSpd_s{};
    // static_param at offset 0x40
    const float* mFinRotate_s{};
    // static_param at offset 0x48
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x50
    const float* mBaseRotRatio_s{};
    // static_param at offset 0x58
    const float* mJustAvoidAngle_s{};
    // static_param at offset 0x60
    const float* mJustAvoidSideDist_s{};
    // static_param at offset 0x68
    const float* mJustAvoidBackDist_s{};
    // static_param at offset 0x70
    const float* mTargetOffsetLowAtRotate_s{};
    // static_param at offset 0x78
    const float* mTargetOffsetHighAtRotate_s{};
    // static_param at offset 0x80
    const bool* mCanBreakIceBlock_s{};
    // static_param at offset 0x88
    const bool* mIsOnSpine1Rotate_s{};
    // static_param at offset 0x90
    const bool* mIsOnSpine2Rotate_s{};
    // static_param at offset 0x98
    const bool* mIsOnSpine3Rotate_s{};
    // static_param at offset 0xa0
    const bool* mCanJustAvoid_s{};
    // static_param at offset 0xa8
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0xb8
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
