#include "Game/AI/Action/actionEventSetDiffuseAttenuate.h"

namespace uking::action {

EventSetDiffuseAttenuate::EventSetDiffuseAttenuate(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventSetDiffuseAttenuate::~EventSetDiffuseAttenuate() = default;

bool EventSetDiffuseAttenuate::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetDiffuseAttenuate::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventSetDiffuseAttenuate::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventSetDiffuseAttenuate::loadParams_() {
    getDynamicParam(&mdiameter_d, "diameter");
}

void EventSetDiffuseAttenuate::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
