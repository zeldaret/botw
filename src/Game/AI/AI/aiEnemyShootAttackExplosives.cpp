#include "Game/AI/AI/aiEnemyShootAttackExplosives.h"

namespace uking::ai {

EnemyShootAttackExplosives::EnemyShootAttackExplosives(const InitArg& arg)
    : EnemyBaseArrowAttack(arg) {}

EnemyShootAttackExplosives::~EnemyShootAttackExplosives() = default;

void EnemyShootAttackExplosives::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBaseArrowAttack::enter_(params);
}

void EnemyShootAttackExplosives::loadParams_() {
    EnemyBaseArrowAttack::loadParams_();
    getStaticParam(&mExplosivesAvoidDist_s, "ExplosivesAvoidDist");
    getStaticParam(&mTurnStartAng_s, "TurnStartAng");
}

}  // namespace uking::ai
