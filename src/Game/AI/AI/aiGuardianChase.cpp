#include "Game/AI/AI/aiGuardianChase.h"

namespace uking::ai {

GuardianChase::GuardianChase(const InitArg& arg) : GuardianAI(arg) {}

GuardianChase::~GuardianChase() = default;

bool GuardianChase::init_(sead::Heap* heap) {
    return GuardianAI::init_(heap);
}

void GuardianChase::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianAI::enter_(params);
}

void GuardianChase::leave_() {
    GuardianAI::leave_();
}

void GuardianChase::loadParams_() {
    GuardianAI::loadParams_();
    getMapUnitParam(&mChaseRange_m, "ChaseRange");
}

}  // namespace uking::ai
