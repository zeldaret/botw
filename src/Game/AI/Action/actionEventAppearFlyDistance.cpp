#include "Game/AI/Action/actionEventAppearFlyDistance.h"

namespace uking::action {

EventAppearFlyDistance::EventAppearFlyDistance(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventAppearFlyDistance::~EventAppearFlyDistance() = default;

bool EventAppearFlyDistance::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventAppearFlyDistance::loadParams_() {
    getDynamicParam(&mGameDataFloatDistance_d, "GameDataFloatDistance");
}

}  // namespace uking::action
