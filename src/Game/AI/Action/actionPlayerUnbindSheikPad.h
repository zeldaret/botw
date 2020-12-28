#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerUnbindSheikPad : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerUnbindSheikPad, PlayerAction)
public:
    explicit PlayerUnbindSheikPad(const InitArg& arg);
    ~PlayerUnbindSheikPad() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
