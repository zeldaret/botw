#pragma once

#include "Game/AI/Action/actionBattleCloseExplosivesAvoidRun.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BattleCloseDangerAvoidRun : public BattleCloseExplosivesAvoidRun {
    SEAD_RTTI_OVERRIDE(BattleCloseDangerAvoidRun, BattleCloseExplosivesAvoidRun)
public:
    explicit BattleCloseDangerAvoidRun(const InitArg& arg);
    ~BattleCloseDangerAvoidRun() override;

    void loadParams_() override;

protected:
    // static_param at offset 0xe0
    const float* mAvoidSubAngle_s{};
};

}  // namespace uking::action
