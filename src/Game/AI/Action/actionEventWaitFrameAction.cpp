#include "Game/AI/Action/actionEventWaitFrameAction.h"

namespace uking::action {

EventWaitFrameAction::EventWaitFrameAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventWaitFrameAction::~EventWaitFrameAction() = default;

bool EventWaitFrameAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventWaitFrameAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventWaitFrameAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventWaitFrameAction::loadParams_() {
    getDynamicParam(&mFrame_d, "Frame");
}

void EventWaitFrameAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
