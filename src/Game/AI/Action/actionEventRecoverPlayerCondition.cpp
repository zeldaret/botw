#include "Game/AI/Action/actionEventRecoverPlayerCondition.h"

namespace uking::action {

EventRecoverPlayerCondition::EventRecoverPlayerCondition(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventRecoverPlayerCondition::~EventRecoverPlayerCondition() = default;

bool EventRecoverPlayerCondition::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventRecoverPlayerCondition::loadParams_() {}

}  // namespace uking::action
