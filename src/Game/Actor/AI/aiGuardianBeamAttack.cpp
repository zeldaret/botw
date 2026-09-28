#include "Game/Actor/AI/aiGuardianBeamAttack.h"

namespace uking::ai {

GuardianBeamAttack::GuardianBeamAttack(const InitArg& arg) : GuardianCommonBeamAttack(arg) {}

GuardianBeamAttack::~GuardianBeamAttack() = default;

bool GuardianBeamAttack::init_(sead::Heap* heap) {
    return GuardianCommonBeamAttack::init_(heap);
}

void GuardianBeamAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianCommonBeamAttack::enter_(params);
}

void GuardianBeamAttack::leave_() {
    GuardianCommonBeamAttack::leave_();
}

void GuardianBeamAttack::loadParams_() {
    GuardianCommonBeamAttack::loadParams_();
    getStaticParam(&mLightRadius_s, "LightRadius");
    getStaticParam(&mLightLength_s, "LightLength");
    getStaticParam(&mLightLengthOffset_s, "LightLengthOffset");
    getStaticParam(&mEarSpeed_s, "EarSpeed");
    getStaticParam(&mAdjustRadius_s, "AdjustRadius");
}

}  // namespace uking::ai
