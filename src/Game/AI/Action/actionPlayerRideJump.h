#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerRideJump : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerRideJump, PlayerAction)
public:
    explicit PlayerRideJump(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mRideOffsetPosY_s{};
    // static_param at offset 0x28
    const float* mRideOffsetPosXZ_s{};
    // static_param at offset 0x30
    const float* mRideJumpTime_s{};
};

}  // namespace uking::action
