#include "Game/AI/Action/actionDemoVisibleOff.h"

namespace uking::action {

DemoVisibleOff::DemoVisibleOff(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DemoVisibleOff::~DemoVisibleOff() = default;

void DemoVisibleOff::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DemoVisibleOff::leave_() {
    ksys::act::ai::Action::leave_();
}

}  // namespace uking::action
