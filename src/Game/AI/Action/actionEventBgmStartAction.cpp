#include "Game/AI/Action/actionEventBgmStartAction.h"

namespace uking::action {

EventBgmStartAction::EventBgmStartAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventBgmStartAction::~EventBgmStartAction() = default;

bool EventBgmStartAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventBgmStartAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventBgmStartAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventBgmStartAction::loadParams_() {
    getDynamicParam(&mBgmName_d, "BgmName");
}

void EventBgmStartAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
