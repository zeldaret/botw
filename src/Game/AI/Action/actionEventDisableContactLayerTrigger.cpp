#include "Game/AI/Action/actionEventDisableContactLayerTrigger.h"

namespace uking::action {

EventDisableContactLayerTrigger::EventDisableContactLayerTrigger(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventDisableContactLayerTrigger::~EventDisableContactLayerTrigger() = default;

bool EventDisableContactLayerTrigger::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventDisableContactLayerTrigger::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventDisableContactLayerTrigger::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventDisableContactLayerTrigger::loadParams_() {
    getDynamicParam(&mContactType_d, "ContactType");
}

void EventDisableContactLayerTrigger::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
