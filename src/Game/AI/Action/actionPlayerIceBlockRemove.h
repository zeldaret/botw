#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerIceBlockRemove : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerIceBlockRemove, PlayerAction)
public:
    explicit PlayerIceBlockRemove(const InitArg& arg);
    ~PlayerIceBlockRemove() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
