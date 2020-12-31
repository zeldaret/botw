#include "Game/AI/AI/aiEnemyPursuingArrowBattle.h"

namespace uking::ai {

EnemyPursuingArrowBattle::EnemyPursuingArrowBattle(const InitArg& arg) : BokoblinArrowBattle(arg) {}

EnemyPursuingArrowBattle::~EnemyPursuingArrowBattle() = default;

void EnemyPursuingArrowBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    BokoblinArrowBattle::enter_(params);
}

void EnemyPursuingArrowBattle::loadParams_() {
    BokoblinArrowBattle::loadParams_();
    getStaticParam(&mPursuingAttackInterval_s, "PursuingAttackInterval");
    getStaticParam(&mPursuingAttackIntervalRand_s, "PursuingAttackIntervalRand");
    getStaticParam(&mPursuingAttackStartDist_s, "PursuingAttackStartDist");
    getStaticParam(&mPursuingAttackStartAng_s, "PursuingAttackStartAng");
}

}  // namespace uking::ai
