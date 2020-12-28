#include "Game/AI/Action/actionBattleWalk.h"

namespace uking::action {

BattleWalk::BattleWalk(const InitArg& arg) : MoveBase(arg) {}

void BattleWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveBase::enter_(params);
}

}  // namespace uking::action
