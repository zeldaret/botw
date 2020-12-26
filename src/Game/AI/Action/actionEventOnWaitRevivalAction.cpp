#include "Game/AI/Action/actionEventOnWaitRevivalAction.h"

namespace uking::action {

EventOnWaitRevivalAction::EventOnWaitRevivalAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventOnWaitRevivalAction::~EventOnWaitRevivalAction() = default;

bool EventOnWaitRevivalAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventOnWaitRevivalAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventOnWaitRevivalAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventOnWaitRevivalAction::loadParams_() {}

void EventOnWaitRevivalAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
