#include "Game/AI/Action/actionEventBgmStopAction.h"

namespace uking::action {

EventBgmStopAction::EventBgmStopAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventBgmStopAction::~EventBgmStopAction() = default;

bool EventBgmStopAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventBgmStopAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventBgmStopAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventBgmStopAction::loadParams_() {
    getDynamicParam(&mFadeSec_d, "FadeSec");
    getDynamicParam(&mBgmName_d, "BgmName");
}

void EventBgmStopAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
