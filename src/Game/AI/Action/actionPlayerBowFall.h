#pragma once

#include "Game/AI/Action/actionPlayerFall.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerBowFall : public PlayerFall {
    SEAD_RTTI_OVERRIDE(PlayerBowFall, PlayerFall)
public:
    explicit PlayerBowFall(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
