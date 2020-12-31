#include "Game/AI/AI/aiEnemyTired.h"

namespace uking::ai {

EnemyTired::EnemyTired(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void EnemyTired::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyTired::loadParams_() {}

}  // namespace uking::ai
