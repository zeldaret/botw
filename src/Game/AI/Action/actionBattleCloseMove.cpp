#include "Game/AI/Action/actionBattleCloseMove.h"

namespace uking::action {

BattleCloseMove::BattleCloseMove(const InitArg& arg) : BattleCloseMoveAction(arg) {}

void BattleCloseMove::enter_(ksys::act::ai::InlineParamPack* params) {
    BattleCloseMoveAction::enter_(params);
}

}  // namespace uking::action
