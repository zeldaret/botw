#pragma once

#include "Game/AI/Action/actionBattleCloseMeanderRun.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BattleCloseMeanderGuardRun : public BattleCloseMeanderRun {
    SEAD_RTTI_OVERRIDE(BattleCloseMeanderGuardRun, BattleCloseMeanderRun)
public:
    explicit BattleCloseMeanderGuardRun(const InitArg& arg);
    ~BattleCloseMeanderGuardRun() override;

protected:
};

}  // namespace uking::action
