#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerRequestRecreateDyeArmor : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerRequestRecreateDyeArmor, PlayerAction)
public:
    explicit PlayerRequestRecreateDyeArmor(const InitArg& arg);
    ~PlayerRequestRecreateDyeArmor() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
