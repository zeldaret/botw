#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerGuardJustFall : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerGuardJustFall, PlayerAction)
public:
    explicit PlayerGuardJustFall(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
