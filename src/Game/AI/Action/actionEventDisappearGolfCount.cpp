#include "Game/AI/Action/actionEventDisappearGolfCount.h"

namespace uking::action {

EventDisappearGolfCount::EventDisappearGolfCount(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventDisappearGolfCount::~EventDisappearGolfCount() = default;

bool EventDisappearGolfCount::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventDisappearGolfCount::loadParams_() {}

}  // namespace uking::action
