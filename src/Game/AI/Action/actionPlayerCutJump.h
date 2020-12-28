#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerCutJump : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerCutJump, PlayerAction)
public:
    explicit PlayerCutJump(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mAttackRatioNSword_s{};
    // static_param at offset 0x28
    const float* mAttackRatioLSword_s{};
    // static_param at offset 0x30
    const float* mAttackRatioSpear_s{};
    // static_param at offset 0x38
    const float* mCutJumpSpeedF_s{};
    // static_param at offset 0x40
    const float* mCutJumpHeight_s{};
    // static_param at offset 0x48
    const float* mCutJumpShortSpeedF_s{};
    // static_param at offset 0x50
    const float* mCutJumpShortHeight_s{};
    // static_param at offset 0x58
    const float* mCutJumpSpeedFLSword_s{};
    // static_param at offset 0x60
    const float* mAimDistOffset_s{};
    // static_param at offset 0x68
    const float* mSwingFrameBeforeGround_s{};
    // static_param at offset 0x70
    const float* mFallSpAttackHeight_s{};
    // static_param at offset 0x78
    const float* mFallSpAttackRadiusMin_s{};
    // static_param at offset 0x80
    const float* mFallSpAttackRadiusMax_s{};
    // static_param at offset 0x88
    const float* mFallSpAttackRadiusAdd_s{};
    // static_param at offset 0x90
    const float* mFallSpAttackRadiusAddLSword_s{};
    // static_param at offset 0x98
    const float* mFallSpAttackCheckUnderDist_s{};
    // static_param at offset 0xa0
    const float* mFallSpLargeAttackRadius_s{};
    // static_param at offset 0xa8
    const int* mRumbleType_s{};
    // static_param at offset 0xb0
    const float* mRumblePowerMin_s{};
    // static_param at offset 0xb8
    const float* mRumblePowerMax_s{};
    // static_param at offset 0xc0
    const float* mParashawlInvalidTime_s{};
};

}  // namespace uking::action
