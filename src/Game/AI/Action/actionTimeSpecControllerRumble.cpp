#include "Game/AI/Action/actionTimeSpecControllerRumble.h"

namespace uking::action {

TimeSpecControllerRumble::TimeSpecControllerRumble(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

TimeSpecControllerRumble::~TimeSpecControllerRumble() = default;

bool TimeSpecControllerRumble::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void TimeSpecControllerRumble::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void TimeSpecControllerRumble::leave_() {
    ksys::act::ai::Action::leave_();
}

void TimeSpecControllerRumble::loadParams_() {
    getStaticParam(&mPattern_s, "Pattern");
    getDynamicParam(&mSeconds_d, "Seconds");
    getDynamicParam(&mIsWait_d, "IsWait");
}

void TimeSpecControllerRumble::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
