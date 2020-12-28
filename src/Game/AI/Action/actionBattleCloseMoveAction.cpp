#include "Game/AI/Action/actionBattleCloseMoveAction.h"

namespace uking::action {

BattleCloseMoveAction::BattleCloseMoveAction(const InitArg& arg) : BattleCloseMoveActionBase(arg) {}

bool BattleCloseMoveAction::init_(sead::Heap* heap) {
    return BattleCloseMoveActionBase::init_(heap);
}

void BattleCloseMoveAction::enter_(ksys::act::ai::InlineParamPack* params) {
    BattleCloseMoveActionBase::enter_(params);
}

void BattleCloseMoveAction::leave_() {
    BattleCloseMoveActionBase::leave_();
}

void BattleCloseMoveAction::calc_() {
    BattleCloseMoveActionBase::calc_();
}

}  // namespace uking::action
