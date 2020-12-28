#pragma once

#include "Game/AI/Action/actionMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BattleWalk : public MoveBase {
    SEAD_RTTI_OVERRIDE(BattleWalk, MoveBase)
public:
    explicit BattleWalk(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
};

}  // namespace uking::action
