#include "Game/AI/Action/actionEventIncreaseFameAction.h"

namespace uking::action {

EventIncreaseFameAction::EventIncreaseFameAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventIncreaseFameAction::~EventIncreaseFameAction() = default;

bool EventIncreaseFameAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventIncreaseFameAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventIncreaseFameAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventIncreaseFameAction::loadParams_() {
    getDynamicParam(&mValue_d, "Value");
}

void EventIncreaseFameAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
