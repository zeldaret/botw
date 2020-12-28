#pragma once

#include "Game/AI/Action/actionActionEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerAction : public ActionEx {
    SEAD_RTTI_OVERRIDE(PlayerAction, ActionEx)
public:
    explicit PlayerAction(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
