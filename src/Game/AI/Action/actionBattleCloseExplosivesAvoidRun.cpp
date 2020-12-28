#include "Game/AI/Action/actionBattleCloseExplosivesAvoidRun.h"

namespace uking::action {

BattleCloseExplosivesAvoidRun::BattleCloseExplosivesAvoidRun(const InitArg& arg)
    : BattleCloseMoveAction(arg) {}

BattleCloseExplosivesAvoidRun::~BattleCloseExplosivesAvoidRun() = default;

void BattleCloseExplosivesAvoidRun::enter_(ksys::act::ai::InlineParamPack* params) {
    BattleCloseMoveAction::enter_(params);
}

void BattleCloseExplosivesAvoidRun::leave_() {
    BattleCloseMoveAction::leave_();
}

void BattleCloseExplosivesAvoidRun::loadParams_() {
    BattleCloseMoveActionBase::loadParams_();
    getStaticParam(&mDamageIgnoreDist_s, "DamageIgnoreDist");
}

}  // namespace uking::action
