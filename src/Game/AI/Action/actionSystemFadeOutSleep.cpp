#include "Game/AI/Action/actionSystemFadeOutSleep.h"

namespace uking::action {

SystemFadeOutSleep::SystemFadeOutSleep(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SystemFadeOutSleep::~SystemFadeOutSleep() = default;

bool SystemFadeOutSleep::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SystemFadeOutSleep::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SystemFadeOutSleep::leave_() {
    ksys::act::ai::Action::leave_();
}

void SystemFadeOutSleep::loadParams_() {}

void SystemFadeOutSleep::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
