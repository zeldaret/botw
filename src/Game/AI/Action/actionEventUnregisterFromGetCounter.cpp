#include "Game/AI/Action/actionEventUnregisterFromGetCounter.h"

namespace uking::action {

EventUnregisterFromGetCounter::EventUnregisterFromGetCounter(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventUnregisterFromGetCounter::~EventUnregisterFromGetCounter() = default;

bool EventUnregisterFromGetCounter::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventUnregisterFromGetCounter::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventUnregisterFromGetCounter::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventUnregisterFromGetCounter::loadParams_() {
    getDynamicParam(&mActorName_d, "ActorName");
}

void EventUnregisterFromGetCounter::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
