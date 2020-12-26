#include "Game/AI/Action/actionEventCancelSleepTargetActor.h"

namespace uking::action {

EventCancelSleepTargetActor::EventCancelSleepTargetActor(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventCancelSleepTargetActor::~EventCancelSleepTargetActor() = default;

bool EventCancelSleepTargetActor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventCancelSleepTargetActor::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventCancelSleepTargetActor::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventCancelSleepTargetActor::loadParams_() {
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mInstanceName_d, "InstanceName");
}

void EventCancelSleepTargetActor::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
