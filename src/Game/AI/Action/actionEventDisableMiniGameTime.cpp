#include "Game/AI/Action/actionEventDisableMiniGameTime.h"

namespace uking::action {

EventDisableMiniGameTime::EventDisableMiniGameTime(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventDisableMiniGameTime::~EventDisableMiniGameTime() = default;

bool EventDisableMiniGameTime::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventDisableMiniGameTime::loadParams_() {}

}  // namespace uking::action
