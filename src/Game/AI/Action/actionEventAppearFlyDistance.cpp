#include "Game/AI/Action/actionEventAppearFlyDistance.h"

namespace uking::action {

EventAppearFlyDistance::EventAppearFlyDistance(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventAppearFlyDistance::~EventAppearFlyDistance() = default;

bool EventAppearFlyDistance::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventAppearFlyDistance::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventAppearFlyDistance::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventAppearFlyDistance::loadParams_() {
    getDynamicParam(&mGameDataFloatDistance_d, "GameDataFloatDistance");
}

void EventAppearFlyDistance::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
