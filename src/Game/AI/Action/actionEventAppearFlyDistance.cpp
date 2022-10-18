#include "Game/AI/Action/actionEventAppearFlyDistance.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

EventAppearFlyDistance::EventAppearFlyDistance(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventAppearFlyDistance::~EventAppearFlyDistance() = default;

bool EventAppearFlyDistance::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool EventAppearFlyDistance::oneShot_() {
    ui::setShowFlyDistance(mGameDataFloatDistance_d);
    return ksys::act::ai::Action::oneShot_();
}

void EventAppearFlyDistance::loadParams_() {
    getDynamicParam(&mGameDataFloatDistance_d, "GameDataFloatDistance");
}

}  // namespace uking::action
