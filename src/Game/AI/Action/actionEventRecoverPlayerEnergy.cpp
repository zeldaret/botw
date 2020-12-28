#include "Game/AI/Action/actionEventRecoverPlayerEnergy.h"

namespace uking::action {

EventRecoverPlayerEnergy::EventRecoverPlayerEnergy(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventRecoverPlayerEnergy::~EventRecoverPlayerEnergy() = default;

bool EventRecoverPlayerEnergy::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventRecoverPlayerEnergy::loadParams_() {}

}  // namespace uking::action
