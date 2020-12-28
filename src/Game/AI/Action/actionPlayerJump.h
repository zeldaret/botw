#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerJump : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerJump, PlayerAction)
public:
    explicit PlayerJump(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mJumpHeight_s{};
    // static_param at offset 0x28
    const float* mJumpHeightAddByAngle_s{};
    // static_param at offset 0x30
    const float* mJumpHeightAddBySpeed_s{};
    // static_param at offset 0x38
    const float* mJumpHeightMaxDecRateByWater_s{};
    // static_param at offset 0x40
    const float* mIgnoreWaterHeight_s{};
    // static_param at offset 0x48
    const float* mEnergyJump_s{};
    // static_param at offset 0x50
    const float* mEnergyDashJump_s{};
    // static_param at offset 0x58
    const float* mEnergyUseDiam1_s{};
    // static_param at offset 0x60
    const float* mEnergyUseDiam2_s{};
    // static_param at offset 0x68
    const float* mEnergyUseDiam3_s{};
};

}  // namespace uking::action
