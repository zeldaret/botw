#include "Game/AI/Action/actionEventSetFocusDist.h"

namespace uking::action {

EventSetFocusDist::EventSetFocusDist(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventSetFocusDist::~EventSetFocusDist() = default;

bool EventSetFocusDist::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetFocusDist::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventSetFocusDist::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventSetFocusDist::loadParams_() {
    getDynamicParam(&mFocusDist_d, "FocusDist");
}

void EventSetFocusDist::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
