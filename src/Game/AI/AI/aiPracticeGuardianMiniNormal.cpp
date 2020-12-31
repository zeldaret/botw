#include "Game/AI/AI/aiPracticeGuardianMiniNormal.h"

namespace uking::ai {

PracticeGuardianMiniNormal::PracticeGuardianMiniNormal(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

PracticeGuardianMiniNormal::~PracticeGuardianMiniNormal() = default;

bool PracticeGuardianMiniNormal::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PracticeGuardianMiniNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PracticeGuardianMiniNormal::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PracticeGuardianMiniNormal::loadParams_() {
    getAITreeVariable(&mGuardianMiniPracticeState_a, "GuardianMiniPracticeState");
}

}  // namespace uking::ai
