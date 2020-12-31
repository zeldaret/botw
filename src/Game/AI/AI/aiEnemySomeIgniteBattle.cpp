#include "Game/AI/AI/aiEnemySomeIgniteBattle.h"

namespace uking::ai {

EnemySomeIgniteBattle::EnemySomeIgniteBattle(const InitArg& arg) : BreathAttackEnemyBattle(arg) {}

EnemySomeIgniteBattle::~EnemySomeIgniteBattle() = default;

void EnemySomeIgniteBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    BreathAttackEnemyBattle::enter_(params);
}

void EnemySomeIgniteBattle::leave_() {
    BreathAttackEnemyBattle::leave_();
}

void EnemySomeIgniteBattle::loadParams_() {
    BreathAttackEnemyBattle::loadParams_();
    getStaticParam(&mIgniteNum_s, "IgniteNum");
}

}  // namespace uking::ai
