#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerLargeDamage : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerLargeDamage, PlayerAction)
public:
    explicit PlayerLargeDamage(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mBaseInitSpeedNSword_s{};
    // static_param at offset 0x28
    const float* mBaseInitSpeedLSword_s{};
    // static_param at offset 0x30
    const float* mBaseInitSpeedSpear_s{};
    // static_param at offset 0x38
    const float* mBaseInitSpeedOther_s{};
    // static_param at offset 0x40
    const float* mAddSpeedNSword_s{};
    // static_param at offset 0x48
    const float* mAddSpeedLSword_s{};
    // static_param at offset 0x50
    const float* mAddSpeedSpear_s{};
    // static_param at offset 0x58
    const float* mAddSpeedOther_s{};
    // static_param at offset 0x60
    const float* mMaxSpeedNSword_s{};
    // static_param at offset 0x68
    const float* mMaxSpeedLSword_s{};
    // static_param at offset 0x70
    const float* mMaxSpeedSpear_s{};
    // static_param at offset 0x78
    const float* mMaxSpeedOther_s{};
    // static_param at offset 0x80
    const float* mJumpHeightNSword_s{};
    // static_param at offset 0x88
    const float* mJumpHeightLSword_s{};
    // static_param at offset 0x90
    const float* mJumpHeightSpear_s{};
    // static_param at offset 0x98
    const float* mJumpHeightOther_s{};
    // static_param at offset 0xa0
    const float* mInitSpeedWind_s{};
    // static_param at offset 0xa8
    const float* mJumpHeightWind_s{};
    // static_param at offset 0xb0
    const float* mNoRagdollTime_s{};
    // static_param at offset 0xb8
    const float* mInitSpeedToss_s{};
    // static_param at offset 0xc0
    const float* mJumpHeightToss_s{};
    // static_param at offset 0xc8
    const float* mAddLinearImpulse_s{};
    // static_param at offset 0xd0
    const float* mAddRollImpulse_s{};
    // static_param at offset 0xd8
    const float* mInitSpeedHorse_s{};
    // static_param at offset 0xe0
    const float* mJumpHeightHorse_s{};
    // static_param at offset 0xe8
    const float* mAddLinearImpulseHorse_s{};
    // static_param at offset 0xf0
    const float* mInitSpeedRynel_s{};
    // static_param at offset 0xf8
    const float* mJumpHeightRynel_s{};
    // static_param at offset 0x100
    const float* mAddLinearImpulseRynel_s{};
    // static_param at offset 0x108
    const float* mAddRollImpulseRynel_s{};
    // static_param at offset 0x110
    const float* mInitSpeedSandworm_s{};
    // static_param at offset 0x118
    const float* mJumpHeightSandworm_s{};
    // static_param at offset 0x120
    const float* mAddLinearImpulseSandworm_s{};
    // static_param at offset 0x128
    const float* mInitSpeedShakeOff_s{};
    // static_param at offset 0x130
    const float* mJumpHeightShakeOff_s{};
    // static_param at offset 0x138
    const float* mAddLinearImpulseShakeOff_s{};
    // static_param at offset 0x140
    const float* mInitSpeedWindRemain_s{};
    // static_param at offset 0x148
    const float* mJumpHeightWindRemain_s{};
    // static_param at offset 0x150
    const float* mAddLinearImpulseWindRemain_s{};
};

}  // namespace uking::action
