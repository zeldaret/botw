#include "Game/AI/AI/aiKorokGoalTimerRootAI.h"

namespace uking::ai {

KorokGoalTimerRootAI::KorokGoalTimerRootAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

KorokGoalTimerRootAI::~KorokGoalTimerRootAI() = default;

bool KorokGoalTimerRootAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void KorokGoalTimerRootAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void KorokGoalTimerRootAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void KorokGoalTimerRootAI::loadParams_() {
    getMapUnitParam(&mGoalCountLimit_m, "GoalCountLimit");
}

}  // namespace uking::ai
