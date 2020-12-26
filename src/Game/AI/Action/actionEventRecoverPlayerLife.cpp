#include "Game/AI/Action/actionEventRecoverPlayerLife.h"

namespace uking::action {

EventRecoverPlayerLife::EventRecoverPlayerLife(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventRecoverPlayerLife::~EventRecoverPlayerLife() = default;

bool EventRecoverPlayerLife::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventRecoverPlayerLife::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventRecoverPlayerLife::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventRecoverPlayerLife::loadParams_() {}

void EventRecoverPlayerLife::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
