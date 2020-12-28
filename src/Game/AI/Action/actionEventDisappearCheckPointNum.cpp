#include "Game/AI/Action/actionEventDisappearCheckPointNum.h"

namespace uking::action {

EventDisappearCheckPointNum::EventDisappearCheckPointNum(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventDisappearCheckPointNum::~EventDisappearCheckPointNum() = default;

bool EventDisappearCheckPointNum::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventDisappearCheckPointNum::loadParams_() {}

}  // namespace uking::action
