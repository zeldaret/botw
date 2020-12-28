#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerAtnMove : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerAtnMove, PlayerAction)
public:
    explicit PlayerAtnMove(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
