#include "Game/AI/Action/actionEventPrizeSuccess.h"

namespace uking::action {

EventPrizeSuccess::EventPrizeSuccess(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventPrizeSuccess::~EventPrizeSuccess() = default;

bool EventPrizeSuccess::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventPrizeSuccess::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventPrizeSuccess::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventPrizeSuccess::loadParams_() {
    getDynamicParam(&mPrizeNumber_d, "PrizeNumber");
}

void EventPrizeSuccess::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
