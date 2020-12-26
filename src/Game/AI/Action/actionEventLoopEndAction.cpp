#include "Game/AI/Action/actionEventLoopEndAction.h"

namespace uking::action {

EventLoopEndAction::EventLoopEndAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventLoopEndAction::~EventLoopEndAction() = default;

bool EventLoopEndAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventLoopEndAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventLoopEndAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventLoopEndAction::loadParams_() {}

void EventLoopEndAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
