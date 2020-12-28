#include "Game/AI/Action/actionEventFlagONAction.h"

namespace uking::action {

EventFlagONAction::EventFlagONAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventFlagONAction::~EventFlagONAction() = default;

bool EventFlagONAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventFlagONAction::loadParams_() {
    getDynamicParam(&mFlagName_d, "FlagName");
}

}  // namespace uking::action
