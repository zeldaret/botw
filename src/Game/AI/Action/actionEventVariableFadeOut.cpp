#include "Game/AI/Action/actionEventVariableFadeOut.h"

namespace uking::action {

EventVariableFadeOut::EventVariableFadeOut(const InitArg& arg) : EventVariableFade(arg) {}

EventVariableFadeOut::~EventVariableFadeOut() = default;

bool EventVariableFadeOut::init_(sead::Heap* heap) {
    return EventVariableFade::init_(heap);
}

void EventVariableFadeOut::enter_(ksys::act::ai::InlineParamPack* params) {
    EventVariableFade::enter_(params);
}

void EventVariableFadeOut::leave_() {
    EventVariableFade::leave_();
}

void EventVariableFadeOut::loadParams_() {
    EventVariableFade::loadParams_();
}

void EventVariableFadeOut::calc_() {
    EventVariableFade::calc_();
}

}  // namespace uking::action
