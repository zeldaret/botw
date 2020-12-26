#include "Game/AI/Action/actionEventSetMoonType.h"

namespace uking::action {

EventSetMoonType::EventSetMoonType(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventSetMoonType::~EventSetMoonType() = default;

bool EventSetMoonType::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetMoonType::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventSetMoonType::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventSetMoonType::loadParams_() {
    getDynamicParam(&mMoonType_d, "MoonType");
}

void EventSetMoonType::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
