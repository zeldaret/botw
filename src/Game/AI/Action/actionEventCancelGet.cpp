#include "Game/AI/Action/actionEventCancelGet.h"

namespace uking::action {

EventCancelGet::EventCancelGet(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventCancelGet::~EventCancelGet() = default;

bool EventCancelGet::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventCancelGet::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventCancelGet::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventCancelGet::loadParams_() {}

void EventCancelGet::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
