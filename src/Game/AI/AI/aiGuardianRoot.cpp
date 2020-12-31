#include "Game/AI/AI/aiGuardianRoot.h"

namespace uking::ai {

GuardianRoot::GuardianRoot(const InitArg& arg) : GuardianAI(arg) {}

GuardianRoot::~GuardianRoot() = default;

bool GuardianRoot::init_(sead::Heap* heap) {
    return GuardianAI::init_(heap);
}

void GuardianRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianAI::enter_(params);
}

void GuardianRoot::leave_() {
    GuardianAI::leave_();
}

void GuardianRoot::loadParams_() {
    GuardianAI::loadParams_();
    getMapUnitParam(&mIsSuspended_m, "IsSuspended");
    getAITreeVariable(&mForceSetDropPos_a, "ForceSetDropPos");
}

}  // namespace uking::ai
