#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerClimbRest : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerClimbRest, PlayerAction)
public:
    explicit PlayerClimbRest(const InitArg& arg);
    ~PlayerClimbRest() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mEnergyClimb_s{};
};

}  // namespace uking::action
