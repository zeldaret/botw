#include "Game/AI/AI/aiSwimEnemyNormal.h"

namespace uking::ai {

SwimEnemyNormal::SwimEnemyNormal(const InitArg& arg) : EnemyNormal(arg) {}

SwimEnemyNormal::~SwimEnemyNormal() = default;

void SwimEnemyNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNormal::enter_(params);
}

void SwimEnemyNormal::leave_() {
    EnemyNormal::leave_();
}

void SwimEnemyNormal::loadParams_() {
    EnemyNormal::loadParams_();
}

}  // namespace uking::ai
