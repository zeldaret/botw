#include "Game/AI/Action/actionEventDisappearRaceResult.h"

namespace uking::action {

EventDisappearRaceResult::EventDisappearRaceResult(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventDisappearRaceResult::~EventDisappearRaceResult() = default;

bool EventDisappearRaceResult::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventDisappearRaceResult::loadParams_() {}

}  // namespace uking::action
