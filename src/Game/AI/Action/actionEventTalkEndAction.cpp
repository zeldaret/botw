#include "Game/AI/Action/actionEventTalkEndAction.h"

namespace uking::action {

EventTalkEndAction::EventTalkEndAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventTalkEndAction::~EventTalkEndAction() = default;

bool EventTalkEndAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventTalkEndAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventTalkEndAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventTalkEndAction::loadParams_() {}

void EventTalkEndAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
