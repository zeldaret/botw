#include "Game/AI/Action/actionFixedMagneStick.h"

namespace uking::action {

FixedMagneStick::FixedMagneStick(const InitArg& arg) : ksys::act::ai::Action(arg) {}

FixedMagneStick::~FixedMagneStick() = default;

bool FixedMagneStick::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void FixedMagneStick::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void FixedMagneStick::leave_() {
    ksys::act::ai::Action::leave_();
}

void FixedMagneStick::loadParams_() {
    getMapUnitParam(&mGrabbedMagneReleaseTime_m, "GrabbedMagneReleaseTime");
    getAITreeVariable(&mMagneStickLength_a, "MagneStickLength");
    getAITreeVariable(&mIsTargetFixedAcceptor_a, "IsTargetFixedAcceptor");
}

void FixedMagneStick::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
