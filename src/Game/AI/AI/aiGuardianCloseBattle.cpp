#include "Game/AI/AI/aiGuardianCloseBattle.h"

namespace uking::ai {

GuardianCloseBattle::GuardianCloseBattle(const InitArg& arg) : GuardianAI(arg) {}

GuardianCloseBattle::~GuardianCloseBattle() = default;

bool GuardianCloseBattle::init_(sead::Heap* heap) {
    return GuardianAI::init_(heap);
}

void GuardianCloseBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianAI::enter_(params);
}

void GuardianCloseBattle::leave_() {
    GuardianAI::leave_();
}

void GuardianCloseBattle::loadParams_() {
    GuardianAI::loadParams_();
}

}  // namespace uking::ai
