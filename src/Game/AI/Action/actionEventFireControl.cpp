#include "Game/AI/Action/actionEventFireControl.h"

namespace uking::action {

EventFireControl::EventFireControl(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventFireControl::~EventFireControl() = default;

bool EventFireControl::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventFireControl::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventFireControl::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventFireControl::loadParams_() {
    getDynamicParam(&mReleaseFire_d, "ReleaseFire");
}

void EventFireControl::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
