#include "Game/AI/AI/aiGuardianMiniRangeKeepMove.h"

namespace uking::ai {

GuardianMiniRangeKeepMove::GuardianMiniRangeKeepMove(const InitArg& arg)
    : EnemyRangeKeepMove(arg) {}

GuardianMiniRangeKeepMove::~GuardianMiniRangeKeepMove() = default;

void GuardianMiniRangeKeepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRangeKeepMove::enter_(params);
}

void GuardianMiniRangeKeepMove::leave_() {
    EnemyRangeKeepMove::leave_();
}

void GuardianMiniRangeKeepMove::loadParams_() {
    EnemyRangeKeepMove::loadParams_();
}

}  // namespace uking::ai
