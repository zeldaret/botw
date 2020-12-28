#include "Game/AI/Action/actionEventCancelSleepTargetActor.h"

namespace uking::action {

EventCancelSleepTargetActor::EventCancelSleepTargetActor(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventCancelSleepTargetActor::~EventCancelSleepTargetActor() = default;

bool EventCancelSleepTargetActor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventCancelSleepTargetActor::loadParams_() {
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mInstanceName_d, "InstanceName");
}

}  // namespace uking::action
