#include "Game/AI/AI/aiGuardianMiniBeamAttackNoWait.h"

namespace uking::ai {

GuardianMiniBeamAttackNoWait::GuardianMiniBeamAttackNoWait(const InitArg& arg)
    : GuardianMiniBeamAttack(arg) {}

GuardianMiniBeamAttackNoWait::~GuardianMiniBeamAttackNoWait() = default;

bool GuardianMiniBeamAttackNoWait::init_(sead::Heap* heap) {
    return GuardianMiniBeamAttack::init_(heap);
}

void GuardianMiniBeamAttackNoWait::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianMiniBeamAttack::enter_(params);
}

void GuardianMiniBeamAttackNoWait::leave_() {
    GuardianMiniBeamAttack::leave_();
}

void GuardianMiniBeamAttackNoWait::loadParams_() {
    GuardianMiniBeamAttack::loadParams_();
    getStaticParam(&mAttackAngle_s, "AttackAngle");
}

}  // namespace uking::ai
