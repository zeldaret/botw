#include "Game/AI/Action/actionEventPrizeSuccess.h"

namespace uking::action {

EventPrizeSuccess::EventPrizeSuccess(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventPrizeSuccess::~EventPrizeSuccess() = default;

void EventPrizeSuccess::loadParams_() {
    getDynamicParam(&mPrizeNumber_d, "PrizeNumber");
}

}  // namespace uking::action
