#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerWakeBoardGoal : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerWakeBoardGoal, PlayerAction)
public:
    explicit PlayerWakeBoardGoal(const InitArg& arg);
    ~PlayerWakeBoardGoal() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    sead::SafeString mASName_d{};
};

}  // namespace uking::action
