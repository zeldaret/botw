#include "Game/AI/Action/actionGuardianMiniFinalBeamMove.h"

namespace uking::action {

GuardianMiniFinalBeamMove::GuardianMiniFinalBeamMove(const InitArg& arg) : GuardianBeamFire(arg) {}

GuardianMiniFinalBeamMove::~GuardianMiniFinalBeamMove() = default;

bool GuardianMiniFinalBeamMove::init_(sead::Heap* heap) {
    return GuardianBeamFire::init_(heap);
}

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
