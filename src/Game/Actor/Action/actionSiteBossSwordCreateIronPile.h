#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossSwordCreateIronPile : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SiteBossSwordCreateIronPile, ksys::act::ai::Action)
public:
    explicit SiteBossSwordCreateIronPile(const InitArg& arg);
    ~SiteBossSwordCreateIronPile() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mCreateNum_s{};
    // static_param at offset 0x28
    const int* mAttackPower_s{};
    // static_param at offset 0x30
    const int* mAtMinDamage_s{};
    // static_param at offset 0x38
    const int* mAttackPowerForPlayer_s{};
    // static_param at offset 0x40
    const int* mAddAttackPower_s{};
    // static_param at offset 0x48
    const float* mAppearPosDist_s{};
    // static_param at offset 0x50
    const float* mAppearPosHeight_s{};
    // static_param at offset 0x58
    const float* mCreateWaitTime_s{};
    // static_param at offset 0x60
    const float* mIgnitionInterval_s{};
    // static_param at offset 0x68
    const float* mPileScale_s{};
    // static_param at offset 0x70
    const float* mNotCreateRange_s{};
    // static_param at offset 0x78
    const bool* mIsRotate_s{};
    // static_param at offset 0x80
    const bool* mIsGuard_s{};
    // static_param at offset 0x88
    const bool* mIsChasePlayer_s{};
    // static_param at offset 0x90
    const bool* mIsRemainBoss_s{};
    // static_param at offset 0x98
    sead::SafeString mWaitAS_s{};
    // static_param at offset 0xa8
    sead::SafeString mCreatePileAS_s{};
    // static_param at offset 0xb8
    sead::SafeString mThunderActorName_s{};
    // static_param at offset 0xc8
    const sead::Vector3f* mNotCreatePosBase_s{};
    // dynamic_param at offset 0xd0
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
