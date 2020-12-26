#include "Game/AI/Action/actionEventIncreaseRupeeAction.h"

namespace uking::action {

EventIncreaseRupeeAction::EventIncreaseRupeeAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventIncreaseRupeeAction::~EventIncreaseRupeeAction() = default;

bool EventIncreaseRupeeAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventIncreaseRupeeAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventIncreaseRupeeAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventIncreaseRupeeAction::loadParams_() {
    getDynamicParam(&mValue_d, "Value");
}

void EventIncreaseRupeeAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
