#pragma once

#include "Game/AI/Action/actionBattleCloseExplosivesAvoidRun.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BattleCloseExplosivesGuardRun : public BattleCloseExplosivesAvoidRun {
    SEAD_RTTI_OVERRIDE(BattleCloseExplosivesGuardRun, BattleCloseExplosivesAvoidRun)
public:
    explicit BattleCloseExplosivesGuardRun(const InitArg& arg);
    ~BattleCloseExplosivesGuardRun() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
};

}  // namespace uking::action
