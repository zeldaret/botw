#include "Game/AI/Action/actionEventRecoverPlayerCondition.h"

namespace uking::action {

EventRecoverPlayerCondition::EventRecoverPlayerCondition(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventRecoverPlayerCondition::~EventRecoverPlayerCondition() = default;

bool EventRecoverPlayerCondition::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventRecoverPlayerCondition::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventRecoverPlayerCondition::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventRecoverPlayerCondition::loadParams_() {}

void EventRecoverPlayerCondition::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
