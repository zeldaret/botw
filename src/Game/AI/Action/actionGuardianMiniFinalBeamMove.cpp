#include "Game/AI/Action/actionGuardianMiniFinalBeamMove.h"

namespace uking::action {

GuardianMiniFinalBeamMove::GuardianMiniFinalBeamMove(const InitArg& arg) : GuardianBeamFire(arg) {}

GuardianMiniFinalBeamMove::~GuardianMiniFinalBeamMove() = default;

void GuardianMiniFinalBeamMove::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianBeamFire::enter_(params);
}

void GuardianMiniFinalBeamMove::leave_() {
    GuardianBeamFire::leave_();
}

void GuardianMiniFinalBeamMove::loadParams_() {
    GuardianBeamFire::loadParams_();
}

void GuardianMiniFinalBeamMove::calc_() {
    GuardianBeamFire::calc_();
}

}  // namespace uking::action
