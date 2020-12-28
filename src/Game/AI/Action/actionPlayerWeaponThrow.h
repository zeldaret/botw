#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerWeaponThrow : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerWeaponThrow, PlayerAction)
public:
    explicit PlayerWeaponThrow(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mThrowSpeedY_s{};
    // static_param at offset 0x28
    const float* mThrowSpeedF_s{};
    // static_param at offset 0x30
    const float* mSquatThrowSpeedF_s{};
};

}  // namespace uking::action
