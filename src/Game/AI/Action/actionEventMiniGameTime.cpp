#include "Game/AI/Action/actionEventMiniGameTime.h"

namespace uking::action {

EventMiniGameTime::EventMiniGameTime(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventMiniGameTime::~EventMiniGameTime() = default;

bool EventMiniGameTime::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventMiniGameTime::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventMiniGameTime::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventMiniGameTime::loadParams_() {
    getDynamicParam(&mCountMode_d, "CountMode");
    getDynamicParam(&mCountStartTime_d, "CountStartTime");
    getDynamicParam(&mMaxTime_d, "MaxTime");
    getDynamicParam(&mIsShowTimeUI_d, "IsShowTimeUI");
}

void EventMiniGameTime::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
