#include "Game/AI/Action/actionEventSetDirectionalLight.h"

namespace uking::action {

EventSetDirectionalLight::EventSetDirectionalLight(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventSetDirectionalLight::~EventSetDirectionalLight() = default;

bool EventSetDirectionalLight::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetDirectionalLight::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventSetDirectionalLight::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventSetDirectionalLight::loadParams_() {
    getDynamicParam(&mangleX_d, "angleX");
    getDynamicParam(&mangleY_d, "angleY");
}

void EventSetDirectionalLight::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
