#include "Game/AI/AI/aiEnemyPursuingAttackCheck.h"

namespace uking::ai {

EnemyPursuingAttackCheck::EnemyPursuingAttackCheck(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyPursuingAttackCheck::~EnemyPursuingAttackCheck() = default;

void EnemyPursuingAttackCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyPursuingAttackCheck::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyPursuingAttackCheck::loadParams_() {
    getStaticParam(&mPursuingAttackInterval_s, "PursuingAttackInterval");
    getStaticParam(&mPursuingAttackIntervalRand_s, "PursuingAttackIntervalRand");
    getStaticParam(&mPursuingAttackStartAng_s, "PursuingAttackStartAng");
    getStaticParam(&mAttackAng_s, "AttackAng");
}

}  // namespace uking::ai
