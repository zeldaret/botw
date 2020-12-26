#include "Game/AI/Action/actionEventSetEnableGrass.h"

namespace uking::action {

EventSetEnableGrass::EventSetEnableGrass(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventSetEnableGrass::~EventSetEnableGrass() = default;

bool EventSetEnableGrass::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetEnableGrass::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventSetEnableGrass::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventSetEnableGrass::loadParams_() {
    getDynamicParam(&mEnable_d, "Enable");
}

void EventSetEnableGrass::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
