#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerMove : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerMove, PlayerAction)
public:
    explicit PlayerMove(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mEnergyDash_s{};
    // static_param at offset 0x28
    const float* mForceApplyPushAnm_s{};
    // static_param at offset 0x30
    const float* mEnergyDashTrig_s{};
    // static_param at offset 0x38
    const float* mPushContinueTime_s{};
    // static_param at offset 0x40
    const float* mPushStopDistY_s{};
    // static_param at offset 0x48
    const float* mInvalidFallFrame_s{};
};

}  // namespace uking::action
