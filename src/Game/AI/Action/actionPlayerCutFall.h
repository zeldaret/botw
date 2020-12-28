#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerCutFall : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerCutFall, PlayerAction)
public:
    explicit PlayerCutFall(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mParashawlInvalidTime_s{};
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
    const float* mFallSpLargeAttackRadius_s{};
    // static_param at offset 0x58
    const int* mRumbleType_s{};
    // static_param at offset 0x60
    const float* mRumblePowerMin_s{};
    // static_param at offset 0x68
    const float* mRumblePowerMax_s{};
};

}  // namespace uking::action
