#include "Game/AI/Action/actionEventDisappearFlyDistance.h"

namespace uking::action {

EventDisappearFlyDistance::EventDisappearFlyDistance(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventDisappearFlyDistance::~EventDisappearFlyDistance() = default;

bool EventDisappearFlyDistance::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventDisappearFlyDistance::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventDisappearFlyDistance::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventDisappearFlyDistance::loadParams_() {}

void EventDisappearFlyDistance::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
