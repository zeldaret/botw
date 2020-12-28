#include "Game/AI/Action/actionEventDisableContactLayerTrigger.h"

namespace uking::action {

EventDisableContactLayerTrigger::EventDisableContactLayerTrigger(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventDisableContactLayerTrigger::~EventDisableContactLayerTrigger() = default;

bool EventDisableContactLayerTrigger::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventDisableContactLayerTrigger::loadParams_() {
    getDynamicParam(&mContactType_d, "ContactType");
}

}  // namespace uking::action
