#pragma once

#include "Game/AI/Action/actionBattleCloseMoveAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BattleCloseGuardRun : public BattleCloseMoveAction {
    SEAD_RTTI_OVERRIDE(BattleCloseGuardRun, BattleCloseMoveAction)
public:
    explicit BattleCloseGuardRun(const InitArg& arg);
    ~BattleCloseGuardRun() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
};

}  // namespace uking::action
