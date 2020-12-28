#include "Game/AI/Action/actionBattleCloseGuardRun.h"

namespace uking::action {

BattleCloseGuardRun::BattleCloseGuardRun(const InitArg& arg) : BattleCloseMoveAction(arg) {}

BattleCloseGuardRun::~BattleCloseGuardRun() = default;

void BattleCloseGuardRun::enter_(ksys::act::ai::InlineParamPack* params) {
    BattleCloseMoveAction::enter_(params);
}

}  // namespace uking::action
