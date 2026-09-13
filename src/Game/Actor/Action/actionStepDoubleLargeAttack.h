#pragma once

#include "Game/Actor/Action/actionStepDoubleAttack.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class StepDoubleLargeAttack : public StepDoubleAttack {
    SEAD_RTTI_OVERRIDE(StepDoubleLargeAttack, StepDoubleAttack)
public:
    explicit StepDoubleLargeAttack(const InitArg& arg);

protected:
};

}  // namespace uking::action
