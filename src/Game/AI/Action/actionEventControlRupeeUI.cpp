#include "Game/AI/Action/actionEventControlRupeeUI.h"

namespace uking::action {

EventControlRupeeUI::EventControlRupeeUI(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventControlRupeeUI::~EventControlRupeeUI() = default;

bool EventControlRupeeUI::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventControlRupeeUI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventControlRupeeUI::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventControlRupeeUI::loadParams_() {
    getDynamicParam(&mTargetValue_d, "TargetValue");
    getDynamicParam(&mIsAppear_d, "IsAppear");
}

void EventControlRupeeUI::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
