#include "Game/Actor/Action/actionBattleCloseMoveAction.h"

namespace uking::action {

BattleCloseMoveAction::BattleCloseMoveAction(const InitArg& arg)
    : AvoidingCloseMoveActionBase(arg) {}

bool BattleCloseMoveAction::init_(sead::Heap* heap) {
    return AvoidingCloseMoveActionBase::init_(heap);
}

void BattleCloseMoveAction::enter_(ksys::act::ai::InlineParamPack* params) {
    AvoidingCloseMoveActionBase::enter_(params);
}

void BattleCloseMoveAction::leave_() {
    AvoidingCloseMoveActionBase::leave_();
}

void BattleCloseMoveAction::calc_() {
    AvoidingCloseMoveActionBase::calc_();
}

}  // namespace uking::action
