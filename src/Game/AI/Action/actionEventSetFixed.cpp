#include "Game/AI/Action/actionEventSetFixed.h"

namespace uking::action {

EventSetFixed::EventSetFixed(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventSetFixed::~EventSetFixed() = default;

bool EventSetFixed::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetFixed::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventSetFixed::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventSetFixed::loadParams_() {
    getAITreeVariable(&mIsChangeToFixedInDemo_a, "IsChangeToFixedInDemo");
}

void EventSetFixed::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
