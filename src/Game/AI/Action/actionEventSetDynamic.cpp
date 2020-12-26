#include "Game/AI/Action/actionEventSetDynamic.h"

namespace uking::action {

EventSetDynamic::EventSetDynamic(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventSetDynamic::~EventSetDynamic() = default;

bool EventSetDynamic::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetDynamic::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventSetDynamic::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventSetDynamic::loadParams_() {
    getAITreeVariable(&mIsChangeToFixedInDemo_a, "IsChangeToFixedInDemo");
}

void EventSetDynamic::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
