#pragma once

#include "Game/AI/Action/actionForkAlwaysTurn.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkTurnASHold : public ForkAlwaysTurn {
    SEAD_RTTI_OVERRIDE(ForkTurnASHold, ForkAlwaysTurn)
public:
    explicit ForkTurnASHold(const InitArg& arg);
    ~ForkTurnASHold() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
