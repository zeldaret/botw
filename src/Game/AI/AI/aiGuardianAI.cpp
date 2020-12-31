#include "Game/AI/AI/aiGuardianAI.h"

namespace uking::ai {

GuardianAI::GuardianAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GuardianAI::~GuardianAI() = default;

bool GuardianAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GuardianAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GuardianAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GuardianAI::loadParams_() {}

}  // namespace uking::ai
