#include "Game/AI/Action/actionGuardianBeamFire.h"

namespace uking::action {

GuardianBeamFire::GuardianBeamFire(const InitArg& arg) : BeamMove(arg) {}

GuardianBeamFire::~GuardianBeamFire() = default;

bool GuardianBeamFire::init_(sead::Heap* heap) {
    return BeamMove::init_(heap);
}

void GuardianBeamFire::enter_(ksys::act::ai::InlineParamPack* params) {
    BeamMove::enter_(params);
}

void GuardianBeamFire::leave_() {
    BeamMove::leave_();
}

void GuardianBeamFire::loadParams_() {
    BeamMove::loadParams_();
    getStaticParam(&mSpeed_s, "Speed");
    getDynamicParam(&mEyePos_d, "EyePos");
}

void GuardianBeamFire::calc_() {
    BeamMove::calc_();
}

}  // namespace uking::action
