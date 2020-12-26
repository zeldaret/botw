#include "Game/AI/Action/actionEventAppearGolfCount.h"

namespace uking::action {

EventAppearGolfCount::EventAppearGolfCount(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventAppearGolfCount::~EventAppearGolfCount() = default;

bool EventAppearGolfCount::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventAppearGolfCount::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventAppearGolfCount::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventAppearGolfCount::loadParams_() {
    getDynamicParam(&mGameDataIntTargetCounter_d, "GameDataIntTargetCounter");
}

void EventAppearGolfCount::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
