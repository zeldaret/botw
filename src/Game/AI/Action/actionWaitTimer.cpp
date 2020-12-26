#include "Game/AI/Action/actionWaitTimer.h"

namespace uking::action {

WaitTimer::WaitTimer(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WaitTimer::~WaitTimer() = default;

bool WaitTimer::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaitTimer::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WaitTimer::leave_() {
    ksys::act::ai::Action::leave_();
}

void WaitTimer::loadParams_() {
    getStaticParam(&mWaitFrame_s, "WaitFrame");
}

void WaitTimer::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
