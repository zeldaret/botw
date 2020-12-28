#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerLadderDownStart : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerLadderDownStart, PlayerAction)
public:
    explicit PlayerLadderDownStart(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
