#include "Game/AI/Action/actionEventRecoverPlayerEnergy.h"

namespace uking::action {

EventRecoverPlayerEnergy::EventRecoverPlayerEnergy(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventRecoverPlayerEnergy::~EventRecoverPlayerEnergy() = default;

bool EventRecoverPlayerEnergy::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventRecoverPlayerEnergy::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventRecoverPlayerEnergy::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventRecoverPlayerEnergy::loadParams_() {}

void EventRecoverPlayerEnergy::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
