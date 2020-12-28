#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerIce : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerIce, PlayerAction)
public:
    explicit PlayerIce(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mEnergyIce_s{};
    // static_param at offset 0x28
    const float* mCountRate_s{};
    // static_param at offset 0x30
    const float* mInputInterval_s{};
    // static_param at offset 0x38
    const float* mJumpSpeedF_s{};
    // static_param at offset 0x40
    const float* mJumpHeight_s{};
    // static_param at offset 0x48
    const float* mJumpSpeedFBlowOff_s{};
    // static_param at offset 0x50
    const float* mJumpHeightBlowOff_s{};
};

}  // namespace uking::action
