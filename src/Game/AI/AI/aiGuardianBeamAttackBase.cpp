#include "Game/AI/AI/aiGuardianBeamAttackBase.h"

namespace uking::ai {

GuardianBeamAttackBase::GuardianBeamAttackBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GuardianBeamAttackBase::~GuardianBeamAttackBase() = default;

bool GuardianBeamAttackBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GuardianBeamAttackBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GuardianBeamAttackBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GuardianBeamAttackBase::loadParams_() {}

}  // namespace uking::ai
