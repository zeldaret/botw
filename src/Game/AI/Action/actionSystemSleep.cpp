#include "Game/AI/Action/actionSystemSleep.h"

namespace uking::action {

SystemSleep::SystemSleep(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SystemSleep::~SystemSleep() = default;

bool SystemSleep::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SystemSleep::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SystemSleep::leave_() {
    ksys::act::ai::Action::leave_();
}

void SystemSleep::loadParams_() {}

void SystemSleep::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
