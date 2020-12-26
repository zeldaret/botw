#include "Game/AI/Action/actionEventFadeOut.h"

namespace uking::action {

EventFadeOut::EventFadeOut(const InitArg& arg) : EventFade(arg) {}

EventFadeOut::~EventFadeOut() = default;

bool EventFadeOut::init_(sead::Heap* heap) {
    return EventFade::init_(heap);
}

void EventFadeOut::enter_(ksys::act::ai::InlineParamPack* params) {
    EventFade::enter_(params);
}

void EventFadeOut::leave_() {
    EventFade::leave_();
}

void EventFadeOut::loadParams_() {
    EventFade::loadParams_();
}

void EventFadeOut::calc_() {
    EventFade::calc_();
}

}  // namespace uking::action
