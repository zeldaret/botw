#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerGuardBreak : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerGuardBreak, PlayerAction)
public:
    explicit PlayerGuardBreak(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
