#include "Game/AI/Action/actionEventFlagOFFAction.h"

namespace uking::action {

EventFlagOFFAction::EventFlagOFFAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventFlagOFFAction::~EventFlagOFFAction() = default;

bool EventFlagOFFAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventFlagOFFAction::loadParams_() {
    getDynamicParam(&mFlagName_d, "FlagName");
}

}  // namespace uking::action
