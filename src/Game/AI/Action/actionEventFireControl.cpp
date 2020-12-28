#include "Game/AI/Action/actionEventFireControl.h"

namespace uking::action {

EventFireControl::EventFireControl(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventFireControl::~EventFireControl() = default;

bool EventFireControl::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventFireControl::loadParams_() {
    getDynamicParam(&mReleaseFire_d, "ReleaseFire");
}

}  // namespace uking::action
