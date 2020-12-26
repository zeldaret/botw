#include "Game/AI/Action/actionEventFade.h"

namespace uking::action {

EventFade::EventFade(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventFade::~EventFade() = default;

bool EventFade::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventFade::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventFade::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventFade::loadParams_() {
    getDynamicParam(&mFrame_d, "Frame");
    getDynamicParam(&mColor_d, "Color");
    getDynamicParam(&mDispMode_d, "DispMode");
}

void EventFade::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
