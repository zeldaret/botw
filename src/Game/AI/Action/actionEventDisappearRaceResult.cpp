#include "Game/AI/Action/actionEventDisappearRaceResult.h"

namespace uking::action {

EventDisappearRaceResult::EventDisappearRaceResult(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventDisappearRaceResult::~EventDisappearRaceResult() = default;

bool EventDisappearRaceResult::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventDisappearRaceResult::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventDisappearRaceResult::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventDisappearRaceResult::loadParams_() {}

void EventDisappearRaceResult::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
