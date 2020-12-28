#pragma once

#include "Game/AI/Action/actionBindAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BowArrowHold : public BindAction {
    SEAD_RTTI_OVERRIDE(BowArrowHold, BindAction)
public:
    explicit BowArrowHold(const InitArg& arg);

protected:
};

}  // namespace uking::action
