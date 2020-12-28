#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerShieldRideMove : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerShieldRideMove, PlayerAction)
public:
    explicit PlayerShieldRideMove(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mMaxSpeed_s{};
    // static_param at offset 0x28
    const float* mJumpSpeedF_s{};
    // static_param at offset 0x30
    const float* mContJumpSpeedF_s{};
    // static_param at offset 0x38
    const float* mJumpHeight_s{};
    // static_param at offset 0x40
    const float* mContJumpInterval_s{};
    // static_param at offset 0x48
    const float* mShieldBreakHeight_s{};
    // static_param at offset 0x50
    const float* mFinishSpeed_s{};
    // static_param at offset 0x58
    const float* mMaxJumpSpeed_s{};
    // static_param at offset 0x60
    const float* mLandSEOnInAirFrame_s{};
};

}  // namespace uking::action
