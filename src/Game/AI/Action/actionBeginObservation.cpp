#include "Game/AI/Action/actionBeginObservation.h"

namespace uking::action {

BeginObservation::BeginObservation(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BeginObservation::~BeginObservation() = default;

bool BeginObservation::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BeginObservation::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BeginObservation::leave_() {
    ksys::act::ai::Action::leave_();
}

void BeginObservation::loadParams_() {
    getMapUnitParam(&mEventFlowName_m, "EventFlowName");
    getMapUnitParam(&mEventFlowEntryName_m, "EventFlowEntryName");
}

void BeginObservation::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
