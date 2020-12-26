#include "Game/AI/Action/actionEventDisappearCheckPointNum.h"

namespace uking::action {

EventDisappearCheckPointNum::EventDisappearCheckPointNum(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventDisappearCheckPointNum::~EventDisappearCheckPointNum() = default;

bool EventDisappearCheckPointNum::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventDisappearCheckPointNum::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventDisappearCheckPointNum::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventDisappearCheckPointNum::loadParams_() {}

void EventDisappearCheckPointNum::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
