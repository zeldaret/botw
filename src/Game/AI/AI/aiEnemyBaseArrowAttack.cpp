#include "Game/AI/AI/aiEnemyBaseArrowAttack.h"

namespace uking::ai {

EnemyBaseArrowAttack::EnemyBaseArrowAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void EnemyBaseArrowAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyBaseArrowAttack::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mIntervalIntensity_s, "IntervalIntensity");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
