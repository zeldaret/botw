#include "Game/AI/Action/actionEventSetFogDirect.h"

namespace uking::action {

EventSetFogDirect::EventSetFogDirect(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventSetFogDirect::~EventSetFogDirect() = default;

bool EventSetFogDirect::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetFogDirect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventSetFogDirect::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventSetFogDirect::loadParams_() {
    getDynamicParam(&mFogRatio_d, "FogRatio");
    getDynamicParam(&mNear_d, "Near");
    getDynamicParam(&mFar_d, "Far");
    getDynamicParam(&mNearUse_d, "NearUse");
    getDynamicParam(&mInstantSW_d, "InstantSW");
    getDynamicParam(&mFarUse_d, "FarUse");
}

void EventSetFogDirect::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
