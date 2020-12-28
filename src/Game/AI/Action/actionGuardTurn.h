#pragma once

#include "Game/AI/Action/actionTurnBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GuardTurn : public TurnBase {
    SEAD_RTTI_OVERRIDE(GuardTurn, TurnBase)
public:
    explicit GuardTurn(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
};

}  // namespace uking::action
