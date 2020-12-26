#include "Game/AI/Action/actionEventDisappearGolfCount.h"

namespace uking::action {

EventDisappearGolfCount::EventDisappearGolfCount(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventDisappearGolfCount::~EventDisappearGolfCount() = default;

bool EventDisappearGolfCount::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventDisappearGolfCount::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventDisappearGolfCount::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventDisappearGolfCount::loadParams_() {}

void EventDisappearGolfCount::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
