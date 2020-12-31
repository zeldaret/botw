#include "Game/AI/AI/aiEnemyAttackAndAway.h"

namespace uking::ai {

EnemyAttackAndAway::EnemyAttackAndAway(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyAttackAndAway::~EnemyAttackAndAway() = default;

void EnemyAttackAndAway::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyAttackAndAway::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mAwayStartDist_s, "AwayStartDist");
    getStaticParam(&mCheckCliffDist_s, "CheckCliffDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
