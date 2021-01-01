#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerDestinationTurnRefActor : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerDestinationTurnRefActor, PlayerAction)
public:
    explicit PlayerDestinationTurnRefActor(const InitArg& arg);
    ~PlayerDestinationTurnRefActor() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    sead::SafeString mUniqName_d{};
};

}  // namespace uking::action
