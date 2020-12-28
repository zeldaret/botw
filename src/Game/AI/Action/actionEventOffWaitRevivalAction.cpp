#include "Game/AI/Action/actionEventOffWaitRevivalAction.h"

namespace uking::action {

EventOffWaitRevivalAction::EventOffWaitRevivalAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventOffWaitRevivalAction::~EventOffWaitRevivalAction() = default;

bool EventOffWaitRevivalAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventOffWaitRevivalAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventOffWaitRevivalAction::loadParams_() {}

void EventOffWaitRevivalAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
