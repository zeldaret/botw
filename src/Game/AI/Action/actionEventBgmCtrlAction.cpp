#include "Game/AI/Action/actionEventBgmCtrlAction.h"

namespace uking::action {

EventBgmCtrlAction::EventBgmCtrlAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventBgmCtrlAction::~EventBgmCtrlAction() = default;

bool EventBgmCtrlAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventBgmCtrlAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventBgmCtrlAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventBgmCtrlAction::loadParams_() {
    getDynamicParam(&mCtrlType_d, "CtrlType");
}

void EventBgmCtrlAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
