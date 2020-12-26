#include "Game/AI/Action/actionEventFadeIn.h"

namespace uking::action {

EventFadeIn::EventFadeIn(const InitArg& arg) : EventFade(arg) {}

EventFadeIn::~EventFadeIn() = default;

bool EventFadeIn::init_(sead::Heap* heap) {
    return EventFade::init_(heap);
}

void EventFadeIn::enter_(ksys::act::ai::InlineParamPack* params) {
    EventFade::enter_(params);
}

void EventFadeIn::leave_() {
    EventFade::leave_();
}

void EventFadeIn::loadParams_() {
    EventFade::loadParams_();
}

void EventFadeIn::calc_() {
    EventFade::calc_();
}

}  // namespace uking::action
