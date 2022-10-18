#include "Game/AI/Action/actionEventAppearRaceResult.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

EventAppearRaceResult::EventAppearRaceResult(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventAppearRaceResult::~EventAppearRaceResult() = default;

bool EventAppearRaceResult::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool EventAppearRaceResult::oneShot_() {
    ui::setShowRaceResult(*mResultType_d);
    return ksys::act::ai::Action::oneShot_();
}

void EventAppearRaceResult::loadParams_() {
    getDynamicParam(&mResultType_d, "ResultType");
}

}  // namespace uking::action
