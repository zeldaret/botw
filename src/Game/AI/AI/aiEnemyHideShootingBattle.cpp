#include "Game/AI/AI/aiEnemyHideShootingBattle.h"

namespace uking::ai {

EnemyHideShootingBattle::EnemyHideShootingBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyHideShootingBattle::~EnemyHideShootingBattle() = default;

void EnemyHideShootingBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyHideShootingBattle::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyHideShootingBattle::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
