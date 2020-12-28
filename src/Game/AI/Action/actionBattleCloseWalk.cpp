#include "Game/AI/Action/actionBattleCloseWalk.h"

namespace uking::action {

BattleCloseWalk::BattleCloseWalk(const InitArg& arg) : BattleCloseMoveAction(arg) {}

bool BattleCloseWalk::init_(sead::Heap* heap) {
    return BattleCloseMoveAction::init_(heap);
}

void BattleCloseWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    BattleCloseMoveAction::enter_(params);
}

void BattleCloseWalk::leave_() {
    BattleCloseMoveAction::leave_();
}

void BattleCloseWalk::loadParams_() {
    BattleCloseMoveActionBase::loadParams_();
}

void BattleCloseWalk::calc_() {
    BattleCloseMoveAction::calc_();
}

}  // namespace uking::action
