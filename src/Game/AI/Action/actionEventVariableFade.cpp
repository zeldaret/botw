#include "Game/AI/Action/actionEventVariableFade.h"

namespace uking::action {

EventVariableFade::EventVariableFade(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventVariableFade::~EventVariableFade() = default;

bool EventVariableFade::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventVariableFade::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventVariableFade::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventVariableFade::loadParams_() {
    getDynamicParam(&mClipIndex_d, "ClipIndex");
    getDynamicParam(&mColor_d, "Color");
    getDynamicParam(&mDuration_d, "Duration");
    getDynamicParam(&mFadeTime_d, "FadeTime");
}

void EventVariableFade::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
