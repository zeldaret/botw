#include "Game/AI/Action/actionEventAppearRaceResult.h"

namespace uking::action {

EventAppearRaceResult::EventAppearRaceResult(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventAppearRaceResult::~EventAppearRaceResult() = default;

bool EventAppearRaceResult::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventAppearRaceResult::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventAppearRaceResult::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventAppearRaceResult::loadParams_() {
    getDynamicParam(&mResultType_d, "ResultType");
}

void EventAppearRaceResult::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
