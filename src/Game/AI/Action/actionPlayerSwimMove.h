#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerSwimMove : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerSwimMove, PlayerAction)
public:
    explicit PlayerSwimMove(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mMaxSpeedF_s{};
    // static_param at offset 0x28
    const float* mMaxSpeedS_s{};
    // static_param at offset 0x30
    const float* mMaxSpeedB_s{};
    // static_param at offset 0x38
    const float* mMaxSpeedDash_s{};
    // static_param at offset 0x40
    const float* mEnergyMove_s{};
    // static_param at offset 0x48
    const float* mEnergyDash_s{};
    // static_param at offset 0x50
    const float* mDecSpeedRate_s{};
};

}  // namespace uking::action
