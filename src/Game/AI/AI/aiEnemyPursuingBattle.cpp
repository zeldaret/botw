#include "Game/AI/AI/aiEnemyPursuingBattle.h"

namespace uking::ai {

EnemyPursuingBattle::EnemyPursuingBattle(const InitArg& arg) : EnemyBattle(arg) {}

EnemyPursuingBattle::~EnemyPursuingBattle() = default;

void EnemyPursuingBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBattle::enter_(params);
}

void EnemyPursuingBattle::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mPursuingAttackInterval_s, "PursuingAttackInterval");
    getStaticParam(&mPursuingAttackIntervalRand_s, "PursuingAttackIntervalRand");
    getStaticParam(&mPursuingAttackStartAng_s, "PursuingAttackStartAng");
}

}  // namespace uking::ai
