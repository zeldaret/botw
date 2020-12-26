#include "Game/AI/Action/actionEventDummyAction.h"

namespace uking::action {

EventDummyAction::EventDummyAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventDummyAction::~EventDummyAction() = default;

bool EventDummyAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventDummyAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventDummyAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventDummyAction::loadParams_() {}

void EventDummyAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
