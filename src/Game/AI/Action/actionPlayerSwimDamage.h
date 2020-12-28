#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerSwimDamage : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerSwimDamage, PlayerAction)
public:
    explicit PlayerSwimDamage(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
