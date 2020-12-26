#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerLadderToClimb : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerLadderToClimb, PlayerAction)
public:
    explicit PlayerLadderToClimb(const InitArg& arg);
    ~PlayerLadderToClimb() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
