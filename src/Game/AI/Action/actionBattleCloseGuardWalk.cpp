#include "Game/AI/Action/actionBattleCloseGuardWalk.h"

namespace uking::action {

BattleCloseGuardWalk::BattleCloseGuardWalk(const InitArg& arg) : BattleCloseMoveAction(arg) {}

bool BattleCloseGuardWalk::init_(sead::Heap* heap) {
    return BattleCloseMoveAction::init_(heap);
}

void BattleCloseGuardWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    BattleCloseMoveAction::enter_(params);
}

void BattleCloseGuardWalk::leave_() {
    BattleCloseMoveAction::leave_();
}

void BattleCloseGuardWalk::loadParams_() {
    BattleCloseMoveActionBase::loadParams_();
}

void BattleCloseGuardWalk::calc_() {
    BattleCloseMoveAction::calc_();
}

}  // namespace uking::action
