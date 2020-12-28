#include "Game/AI/Action/actionEventIncreaseRupeeAction.h"

namespace uking::action {

EventIncreaseRupeeAction::EventIncreaseRupeeAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

void EventIncreaseRupeeAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventIncreaseRupeeAction::loadParams_() {
    getDynamicParam(&mValue_d, "Value");
}

void EventIncreaseRupeeAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
