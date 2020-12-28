#include "Game/AI/Action/actionEventUnregisterFromDeathCounter.h"

namespace uking::action {

EventUnregisterFromDeathCounter::EventUnregisterFromDeathCounter(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventUnregisterFromDeathCounter::~EventUnregisterFromDeathCounter() = default;

bool EventUnregisterFromDeathCounter::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventUnregisterFromDeathCounter::loadParams_() {
    getDynamicParam(&mActorName_d, "ActorName");
}

}  // namespace uking::action
