#include "Game/AI/AI/aiGuardianDown.h"

namespace uking::ai {

GuardianDown::GuardianDown(const InitArg& arg) : GuardianAI(arg) {}

GuardianDown::~GuardianDown() = default;

bool GuardianDown::init_(sead::Heap* heap) {
    return GuardianAI::init_(heap);
}

void GuardianDown::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianAI::enter_(params);
}

void GuardianDown::leave_() {
    GuardianAI::leave_();
}

void GuardianDown::loadParams_() {
    GuardianAI::loadParams_();
}

}  // namespace uking::ai
