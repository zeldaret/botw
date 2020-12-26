#include "Game/AI/Action/actionForkOverrideStartNoDrawTimer.h"

namespace uking::action {

ForkOverrideStartNoDrawTimer::ForkOverrideStartNoDrawTimer(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkOverrideStartNoDrawTimer::~ForkOverrideStartNoDrawTimer() = default;

bool ForkOverrideStartNoDrawTimer::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkOverrideStartNoDrawTimer::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkOverrideStartNoDrawTimer::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkOverrideStartNoDrawTimer::loadParams_() {
    getStaticParam(&mTime_s, "Time");
}

void ForkOverrideStartNoDrawTimer::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
