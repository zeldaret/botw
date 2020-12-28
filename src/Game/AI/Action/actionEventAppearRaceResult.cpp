#include "Game/AI/Action/actionEventAppearRaceResult.h"

namespace uking::action {

EventAppearRaceResult::EventAppearRaceResult(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventAppearRaceResult::~EventAppearRaceResult() = default;

bool EventAppearRaceResult::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventAppearRaceResult::loadParams_() {
    getDynamicParam(&mResultType_d, "ResultType");
}

}  // namespace uking::action
