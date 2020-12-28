#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerIceGrabReady : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerIceGrabReady, PlayerAction)
public:
    explicit PlayerIceGrabReady(const InitArg& arg);
    ~PlayerIceGrabReady() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
