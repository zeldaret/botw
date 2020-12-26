#include "Game/AI/Action/actionEventChangeShadowNearAndFar.h"

namespace uking::action {

EventChangeShadowNearAndFar::EventChangeShadowNearAndFar(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventChangeShadowNearAndFar::~EventChangeShadowNearAndFar() = default;

bool EventChangeShadowNearAndFar::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventChangeShadowNearAndFar::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventChangeShadowNearAndFar::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventChangeShadowNearAndFar::loadParams_() {
    getDynamicParam(&mManualNearValue_d, "ManualNearValue");
    getDynamicParam(&mManualFarValue_d, "ManualFarValue");
    getDynamicParam(&mIsNearSetManual_d, "IsNearSetManual");
    getDynamicParam(&mIsFarSetManual_d, "IsFarSetManual");
}

void EventChangeShadowNearAndFar::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
