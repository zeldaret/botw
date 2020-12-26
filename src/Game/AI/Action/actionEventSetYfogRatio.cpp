#include "Game/AI/Action/actionEventSetYfogRatio.h"

namespace uking::action {

EventSetYfogRatio::EventSetYfogRatio(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventSetYfogRatio::~EventSetYfogRatio() = default;

bool EventSetYfogRatio::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetYfogRatio::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventSetYfogRatio::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventSetYfogRatio::loadParams_() {
    getDynamicParam(&mYfogRatio_d, "YfogRatio");
}

void EventSetYfogRatio::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
