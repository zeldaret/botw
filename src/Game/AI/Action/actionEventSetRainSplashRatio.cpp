#include "Game/AI/Action/actionEventSetRainSplashRatio.h"

namespace uking::action {

EventSetRainSplashRatio::EventSetRainSplashRatio(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventSetRainSplashRatio::~EventSetRainSplashRatio() = default;

bool EventSetRainSplashRatio::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetRainSplashRatio::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventSetRainSplashRatio::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventSetRainSplashRatio::loadParams_() {
    getDynamicParam(&mRainSplashRatio_d, "RainSplashRatio");
}

void EventSetRainSplashRatio::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
