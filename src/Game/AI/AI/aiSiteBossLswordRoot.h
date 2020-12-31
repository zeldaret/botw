#pragma once

#include "Game/AI/AI/aiSiteBossRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossLswordRoot : public SiteBossRoot {
    SEAD_RTTI_OVERRIDE(SiteBossLswordRoot, SiteBossRoot)
public:
    explicit SiteBossLswordRoot(const InitArg& arg);
    ~SiteBossLswordRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xf8
    const int* mFireBallAttackPower_s{};
    // static_param at offset 0x100
    const int* mFireBallMinDamage_s{};
    // static_param at offset 0x108
    const int* mBigFireBallAttackPower_s{};
    // static_param at offset 0x110
    const int* mBigFireBallMinDamage_s{};
    // static_param at offset 0x118
    const int* mWearFlameAttackPower_s{};
    // static_param at offset 0x120
    const int* mWearFlameMinDamage_s{};
    // static_param at offset 0x128
    const float* mBigFireBallScaleTime0_s{};
    // static_param at offset 0x130
    const float* mBigFireBallScaleMax_s{};
    // static_param at offset 0x138
    const float* mBigFireBallScaleTime1_s{};
    // static_param at offset 0x140
    const float* mBigFireBallMoveSpeed0_s{};
    // static_param at offset 0x148
    const float* mBigFireBallMoveSpeed1_s{};
    // static_param at offset 0x150
    const sead::Vector3f* mBigFireBallPosOffset_s{};
    // static_param at offset 0x158
    const sead::Vector3f* mBigFireBallRotOffset_s{};
};

}  // namespace uking::ai
