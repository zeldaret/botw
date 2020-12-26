#include "Game/AI/Action/actionEventVariableFadeIn.h"

namespace uking::action {

EventVariableFadeIn::EventVariableFadeIn(const InitArg& arg) : EventVariableFade(arg) {}

EventVariableFadeIn::~EventVariableFadeIn() = default;

bool EventVariableFadeIn::init_(sead::Heap* heap) {
    return EventVariableFade::init_(heap);
}

void EventVariableFadeIn::enter_(ksys::act::ai::InlineParamPack* params) {
    EventVariableFade::enter_(params);
}

void EventVariableFadeIn::leave_() {
    EventVariableFade::leave_();
}

void EventVariableFadeIn::loadParams_() {
    EventVariableFade::loadParams_();
}

void EventVariableFadeIn::calc_() {
    EventVariableFade::calc_();
}

}  // namespace uking::action
