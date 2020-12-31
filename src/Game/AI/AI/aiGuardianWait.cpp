#include "Game/AI/AI/aiGuardianWait.h"

namespace uking::ai {

GuardianWait::GuardianWait(const InitArg& arg) : GuardianAI(arg) {}

GuardianWait::~GuardianWait() = default;

bool GuardianWait::init_(sead::Heap* heap) {
    return GuardianAI::init_(heap);
}

void GuardianWait::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianAI::enter_(params);
}

void GuardianWait::leave_() {
    GuardianAI::leave_();
}

void GuardianWait::loadParams_() {
    GuardianAI::loadParams_();
}

}  // namespace uking::ai
