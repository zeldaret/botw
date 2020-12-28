#include "Game/AI/Action/actionBattleCloseDangerAvoidRun.h"

namespace uking::action {

BattleCloseDangerAvoidRun::BattleCloseDangerAvoidRun(const InitArg& arg)
    : BattleCloseExplosivesAvoidRun(arg) {}

BattleCloseDangerAvoidRun::~BattleCloseDangerAvoidRun() = default;

void BattleCloseDangerAvoidRun::loadParams_() {
    BattleCloseExplosivesAvoidRun::loadParams_();
    getStaticParam(&mAvoidSubAngle_s, "AvoidSubAngle");
}

}  // namespace uking::action
