#include "Game/AI/Action/actionBattleCloseExplosivesGuardRun.h"

namespace uking::action {

BattleCloseExplosivesGuardRun::BattleCloseExplosivesGuardRun(const InitArg& arg)
    : BattleCloseExplosivesAvoidRun(arg) {}

BattleCloseExplosivesGuardRun::~BattleCloseExplosivesGuardRun() = default;

void BattleCloseExplosivesGuardRun::enter_(ksys::act::ai::InlineParamPack* params) {
    BattleCloseExplosivesAvoidRun::enter_(params);
}

}  // namespace uking::action
