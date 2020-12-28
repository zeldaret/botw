#pragma once

#include "Game/AI/Action/actionTurnBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Turn : public TurnBase {
    SEAD_RTTI_OVERRIDE(Turn, TurnBase)
public:
    explicit Turn(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
};

}  // namespace uking::action
