#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerLadderMove : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerLadderMove, PlayerAction)
public:
    explicit PlayerLadderMove(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mDownMoveSpeed_s{};
};

}  // namespace uking::action
