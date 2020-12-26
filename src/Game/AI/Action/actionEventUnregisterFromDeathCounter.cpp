#include "Game/AI/Action/actionEventUnregisterFromDeathCounter.h"

namespace uking::action {

EventUnregisterFromDeathCounter::EventUnregisterFromDeathCounter(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventUnregisterFromDeathCounter::~EventUnregisterFromDeathCounter() = default;

bool EventUnregisterFromDeathCounter::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventUnregisterFromDeathCounter::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventUnregisterFromDeathCounter::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventUnregisterFromDeathCounter::loadParams_() {
    getDynamicParam(&mActorName_d, "ActorName");
}

void EventUnregisterFromDeathCounter::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
