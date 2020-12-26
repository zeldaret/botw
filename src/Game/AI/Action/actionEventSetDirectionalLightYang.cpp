#include "Game/AI/Action/actionEventSetDirectionalLightYang.h"

namespace uking::action {

EventSetDirectionalLightYang::EventSetDirectionalLightYang(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventSetDirectionalLightYang::~EventSetDirectionalLightYang() = default;

bool EventSetDirectionalLightYang::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetDirectionalLightYang::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventSetDirectionalLightYang::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventSetDirectionalLightYang::loadParams_() {
    getDynamicParam(&mangleY_d, "angleY");
}

void EventSetDirectionalLightYang::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
