#include "Game/AI/Action/actionEventDisableMiniGameTime.h"

namespace uking::action {

EventDisableMiniGameTime::EventDisableMiniGameTime(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventDisableMiniGameTime::~EventDisableMiniGameTime() = default;

bool EventDisableMiniGameTime::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventDisableMiniGameTime::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventDisableMiniGameTime::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventDisableMiniGameTime::loadParams_() {}

void EventDisableMiniGameTime::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
