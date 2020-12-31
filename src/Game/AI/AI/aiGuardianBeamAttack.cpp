#include "Game/AI/AI/aiGuardianBeamAttack.h"

namespace uking::ai {

GuardianBeamAttack::GuardianBeamAttack(const InitArg& arg) : GuardianBeamAttackBase(arg) {}

GuardianBeamAttack::~GuardianBeamAttack() = default;

bool GuardianBeamAttack::init_(sead::Heap* heap) {
    return GuardianBeamAttackBase::init_(heap);
}

void GuardianBeamAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianBeamAttackBase::enter_(params);
}

void GuardianBeamAttack::leave_() {
    GuardianBeamAttackBase::leave_();
}

void GuardianBeamAttack::loadParams_() {
    GuardianBeamAttackBase::loadParams_();
    getStaticParam(&mLightRadius_s, "LightRadius");
    getStaticParam(&mLightLength_s, "LightLength");
    getStaticParam(&mLightLengthOffset_s, "LightLengthOffset");
    getStaticParam(&mEarSpeed_s, "EarSpeed");
    getStaticParam(&mAdjustRadius_s, "AdjustRadius");
}

}  // namespace uking::ai
