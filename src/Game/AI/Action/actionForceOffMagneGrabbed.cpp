#include "Game/AI/Action/actionForceOffMagneGrabbed.h"

namespace uking::action {

ForceOffMagneGrabbed::ForceOffMagneGrabbed(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForceOffMagneGrabbed::~ForceOffMagneGrabbed() = default;

bool ForceOffMagneGrabbed::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForceOffMagneGrabbed::loadParams_() {}

}  // namespace uking::action
