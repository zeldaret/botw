#pragma once

#include "Game/AI/Action/actionBattleCloseMoveAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BattleCloseMove : public BattleCloseMoveAction {
    SEAD_RTTI_OVERRIDE(BattleCloseMove, BattleCloseMoveAction)
public:
    explicit BattleCloseMove(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
};

}  // namespace uking::action
