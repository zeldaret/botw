#include "Game/AI/Action/actionBattleCloseGuardRun.h"

namespace uking::action {

BattleCloseGuardRun::BattleCloseGuardRun(const InitArg& arg) : BattleCloseMoveAction(arg) {}

BattleCloseGuardRun::~BattleCloseGuardRun() = default;

bool BattleCloseGuardRun::init_(sead::Heap* heap) {
    return BattleCloseMoveAction::init_(heap);
}

void BattleCloseGuardRun::enter_(ksys::act::ai::InlineParamPack* params) {
    BattleCloseMoveAction::enter_(params);
}

void BattleCloseGuardRun::leave_() {
    BattleCloseMoveAction::leave_();
}

void BattleCloseGuardRun::loadParams_() {
    BattleCloseAction::loadParams_();
}

void BattleCloseGuardRun::calc_() {
    BattleCloseMoveAction::calc_();
}

}  // namespace uking::action
