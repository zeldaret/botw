#pragma once

#include "Game/AI/Action/actionTurnBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GrabRightTurn : public TurnBase {
    SEAD_RTTI_OVERRIDE(GrabRightTurn, TurnBase)
public:
    explicit GrabRightTurn(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
};

}  // namespace uking::action
