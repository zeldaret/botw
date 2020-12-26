#include "Game/AI/Action/actionForceOffMagneGrabbed.h"

namespace uking::action {

ForceOffMagneGrabbed::ForceOffMagneGrabbed(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForceOffMagneGrabbed::~ForceOffMagneGrabbed() = default;

bool ForceOffMagneGrabbed::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForceOffMagneGrabbed::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForceOffMagneGrabbed::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForceOffMagneGrabbed::loadParams_() {}

void ForceOffMagneGrabbed::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
