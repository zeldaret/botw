#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerCutTurnLSword : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerCutTurnLSword, PlayerAction)
public:
    explicit PlayerCutTurnLSword(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mEnergyMove_s{};
    // static_param at offset 0x28
    const float* mEnergyLastAttack_s{};
    // static_param at offset 0x30
    const float* mMaxSpeedF_s{};
    // static_param at offset 0x38
    const float* mAccSpeed_s{};
    // static_param at offset 0x40
    const float* mDecSpeed_s{};
    // static_param at offset 0x48
    const float* mSpAttackRadiusMin_s{};
    // static_param at offset 0x50
    const float* mSpAttackRadiusMax_s{};
    // static_param at offset 0x58
    const float* mSpAttackRadiusAdd_s{};
    // static_param at offset 0x60
    const float* mSpAttackCheckUnderDist_s{};
    // static_param at offset 0x68
    const float* mSpLargeAttackRadius_s{};
    // static_param at offset 0x70
    const int* mRumbleType_s{};
    // static_param at offset 0x78
    const float* mRumblePowerMin_s{};
    // static_param at offset 0x80
    const float* mRumblePowerMax_s{};
    // static_param at offset 0x88
    const float* mEnergyChargeStart_s{};
};

}  // namespace uking::action
