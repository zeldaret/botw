#include "Game/AI/Action/actionEventSleepTargetActor.h"

namespace uking::action {

EventSleepTargetActor::EventSleepTargetActor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventSleepTargetActor::~EventSleepTargetActor() = default;

bool EventSleepTargetActor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSleepTargetActor::loadParams_() {
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mInstanceName_d, "InstanceName");
}

}  // namespace uking::action
