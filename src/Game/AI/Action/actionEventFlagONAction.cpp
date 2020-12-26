#include "Game/AI/Action/actionEventFlagONAction.h"

namespace uking::action {

EventFlagONAction::EventFlagONAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventFlagONAction::~EventFlagONAction() = default;

bool EventFlagONAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventFlagONAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventFlagONAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventFlagONAction::loadParams_() {
    getDynamicParam(&mFlagName_d, "FlagName");
}

void EventFlagONAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
