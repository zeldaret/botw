#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerCutHorseJump : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerCutHorseJump, PlayerAction)
public:
    explicit PlayerCutHorseJump(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mAttackRate_s{};
    // static_param at offset 0x28
    const float* mFallSpAttackHeight_s{};
    // static_param at offset 0x30
    const float* mFallSpAttackRadiusMin_s{};
    // static_param at offset 0x38
    const float* mFallSpAttackRadiusMax_s{};
    // static_param at offset 0x40
    const float* mFallSpAttackRadiusAdd_s{};
    // static_param at offset 0x48
    const float* mFallSpAttackRadiusAddLSword_s{};
    // static_param at offset 0x50
    const float* mFallSpAttackCheckUnderDist_s{};
    // static_param at offset 0x58
    const float* mFallSpLargeAttackRadius_s{};
    // static_param at offset 0x60
    const int* mRumbleType_s{};
    // static_param at offset 0x68
    const float* mRumblePowerMin_s{};
    // static_param at offset 0x70
    const float* mRumblePowerMax_s{};
    // static_param at offset 0x78
    const float* mParashawlInvalidTime_s{};
};

}  // namespace uking::action
