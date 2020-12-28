#include "Game/AI/Action/actionEventUnregisterFromGetCounter.h"

namespace uking::action {

EventUnregisterFromGetCounter::EventUnregisterFromGetCounter(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventUnregisterFromGetCounter::~EventUnregisterFromGetCounter() = default;

bool EventUnregisterFromGetCounter::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventUnregisterFromGetCounter::loadParams_() {
    getDynamicParam(&mActorName_d, "ActorName");
}

}  // namespace uking::action
