#include "Game/AI/Action/actionEventDisappearFlyDistance.h"

namespace uking::action {

EventDisappearFlyDistance::EventDisappearFlyDistance(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventDisappearFlyDistance::~EventDisappearFlyDistance() = default;

bool EventDisappearFlyDistance::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventDisappearFlyDistance::loadParams_() {}

}  // namespace uking::action
