#pragma once

#include "Game/AI/Action/actionPlayerStoleOpenBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerStoleOpenEx : public PlayerStoleOpenBase {
    SEAD_RTTI_OVERRIDE(PlayerStoleOpenEx, PlayerStoleOpenBase)
public:
    explicit PlayerStoleOpenEx(const InitArg& arg);

protected:
};

}  // namespace uking::action
