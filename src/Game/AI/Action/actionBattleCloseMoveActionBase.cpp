#include "Game/AI/Action/actionBattleCloseMoveActionBase.h"

namespace uking::action {

BattleCloseMoveActionBase::BattleCloseMoveActionBase(const InitArg& arg) : BattleCloseAction(arg) {}

BattleCloseMoveActionBase::~BattleCloseMoveActionBase() = default;

bool BattleCloseMoveActionBase::init_(sead::Heap* heap) {
    return BattleCloseAction::init_(heap);
}

void BattleCloseMoveActionBase::enter_(ksys::act::ai::InlineParamPack* params) {
    BattleCloseAction::enter_(params);
}

void BattleCloseMoveActionBase::leave_() {
    BattleCloseAction::leave_();
}

void BattleCloseMoveActionBase::loadParams_() {
    BattleCloseAction::loadParams_();
}

void BattleCloseMoveActionBase::calc_() {
    BattleCloseAction::calc_();
}

}  // namespace uking::action
