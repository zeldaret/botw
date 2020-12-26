#include "Game/AI/Action/actionBattleCloseExplosivesGuardRun.h"

namespace uking::action {

BattleCloseExplosivesGuardRun::BattleCloseExplosivesGuardRun(const InitArg& arg)
    : BattleCloseExplosivesAvoidRun(arg) {}

BattleCloseExplosivesGuardRun::~BattleCloseExplosivesGuardRun() = default;

bool BattleCloseExplosivesGuardRun::init_(sead::Heap* heap) {
    return BattleCloseExplosivesAvoidRun::init_(heap);
}

void BattleCloseExplosivesGuardRun::enter_(ksys::act::ai::InlineParamPack* params) {
    BattleCloseExplosivesAvoidRun::enter_(params);
}

void BattleCloseExplosivesGuardRun::leave_() {
    BattleCloseExplosivesAvoidRun::leave_();
}

void BattleCloseExplosivesGuardRun::loadParams_() {
    BattleCloseMoveActionBase::loadParams_();
    getStaticParam(&mDamageIgnoreDist_s, "DamageIgnoreDist");
}

void BattleCloseExplosivesGuardRun::calc_() {
    BattleCloseExplosivesAvoidRun::calc_();
}

}  // namespace uking::action
