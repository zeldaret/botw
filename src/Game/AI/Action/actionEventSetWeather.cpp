#include "Game/AI/Action/actionEventSetWeather.h"

namespace uking::action {

EventSetWeather::EventSetWeather(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventSetWeather::~EventSetWeather() = default;

bool EventSetWeather::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetWeather::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventSetWeather::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventSetWeather::loadParams_() {
    getDynamicParam(&mWeatherType_d, "WeatherType");
}

void EventSetWeather::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
