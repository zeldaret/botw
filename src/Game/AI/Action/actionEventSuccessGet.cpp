#include "Game/AI/Action/actionEventSuccessGet.h"

namespace uking::action {

EventSuccessGet::EventSuccessGet(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventSuccessGet::~EventSuccessGet() = default;

bool EventSuccessGet::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSuccessGet::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventSuccessGet::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventSuccessGet::loadParams_() {}

void EventSuccessGet::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
