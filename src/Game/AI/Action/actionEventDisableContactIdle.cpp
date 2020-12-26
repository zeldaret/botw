#include "Game/AI/Action/actionEventDisableContactIdle.h"

namespace uking::action {

EventDisableContactIdle::EventDisableContactIdle(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventDisableContactIdle::~EventDisableContactIdle() = default;

bool EventDisableContactIdle::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventDisableContactIdle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventDisableContactIdle::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventDisableContactIdle::loadParams_() {
    getDynamicParam(&mContactType_d, "ContactType");
}

void EventDisableContactIdle::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
