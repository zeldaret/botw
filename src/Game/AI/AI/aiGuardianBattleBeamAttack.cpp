#include "Game/AI/AI/aiGuardianBattleBeamAttack.h"

namespace uking::ai {

GuardianBattleBeamAttack::GuardianBattleBeamAttack(const InitArg& arg) : GuardianAI(arg) {}

GuardianBattleBeamAttack::~GuardianBattleBeamAttack() = default;

bool GuardianBattleBeamAttack::init_(sead::Heap* heap) {
    return GuardianAI::init_(heap);
}

void GuardianBattleBeamAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianAI::enter_(params);
}

void GuardianBattleBeamAttack::leave_() {
    GuardianAI::leave_();
}

void GuardianBattleBeamAttack::loadParams_() {
    GuardianAI::loadParams_();
}

}  // namespace uking::ai
