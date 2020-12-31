#include "Game/AI/AI/aiEnemyTargetInSightSelect.h"

namespace uking::ai {

EnemyTargetInSightSelect::EnemyTargetInSightSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyTargetInSightSelect::~EnemyTargetInSightSelect() = default;

void EnemyTargetInSightSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyTargetInSightSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

}  // namespace uking::ai
