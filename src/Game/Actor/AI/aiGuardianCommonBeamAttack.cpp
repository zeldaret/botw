#include "Game/Actor/AI/aiGuardianCommonBeamAttack.h"

namespace uking::ai {

GuardianCommonBeamAttack::GuardianCommonBeamAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GuardianCommonBeamAttack::~GuardianCommonBeamAttack() = default;

bool GuardianCommonBeamAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GuardianCommonBeamAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GuardianCommonBeamAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GuardianCommonBeamAttack::loadParams_() {}

}  // namespace uking::ai
