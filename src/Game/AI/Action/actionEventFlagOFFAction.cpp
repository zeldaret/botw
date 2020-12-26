#include "Game/AI/Action/actionEventFlagOFFAction.h"

namespace uking::action {

EventFlagOFFAction::EventFlagOFFAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventFlagOFFAction::~EventFlagOFFAction() = default;

bool EventFlagOFFAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventFlagOFFAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventFlagOFFAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventFlagOFFAction::loadParams_() {
    getDynamicParam(&mFlagName_d, "FlagName");
}

void EventFlagOFFAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
