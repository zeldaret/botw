#include "Game/AI/AI/aiEnemyAngry.h"

namespace uking::ai {

EnemyAngry::EnemyAngry(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void EnemyAngry::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyAngry::loadParams_() {
    getStaticParam(&mTurnAng_s, "TurnAng");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
