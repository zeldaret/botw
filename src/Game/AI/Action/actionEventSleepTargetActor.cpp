#include "Game/AI/Action/actionEventSleepTargetActor.h"

namespace uking::action {

EventSleepTargetActor::EventSleepTargetActor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventSleepTargetActor::~EventSleepTargetActor() = default;

bool EventSleepTargetActor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSleepTargetActor::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventSleepTargetActor::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventSleepTargetActor::loadParams_() {
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mInstanceName_d, "InstanceName");
}

void EventSleepTargetActor::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
