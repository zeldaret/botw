#include "Game/AI/Action/actionEventCancelGet.h"

namespace uking::action {

EventCancelGet::EventCancelGet(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventCancelGet::~EventCancelGet() = default;

bool EventCancelGet::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventCancelGet::loadParams_() {}

}  // namespace uking::action
