#pragma once

#include "Game/AI/Action/actionTurnBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GrabLeftTurn : public TurnBase {
    SEAD_RTTI_OVERRIDE(GrabLeftTurn, TurnBase)
public:
    explicit GrabLeftTurn(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
};

}  // namespace uking::action
