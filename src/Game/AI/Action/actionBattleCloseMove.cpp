#include "Game/AI/Action/actionBattleCloseMove.h"

namespace uking::action {

BattleCloseMove::BattleCloseMove(const InitArg& arg) : BattleCloseMoveAction(arg) {}

BattleCloseMove::~BattleCloseMove() = default;

bool BattleCloseMove::init_(sead::Heap* heap) {
    return BattleCloseMoveAction::init_(heap);
}

void BattleCloseMove::enter_(ksys::act::ai::InlineParamPack* params) {
    BattleCloseMoveAction::enter_(params);
}

void BattleCloseMove::leave_() {
    BattleCloseMoveAction::leave_();
}

void BattleCloseMove::loadParams_() {
    BattleCloseAction::loadParams_();
}

void BattleCloseMove::calc_() {
    BattleCloseMoveAction::calc_();
}

}  // namespace uking::action
