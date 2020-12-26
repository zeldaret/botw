#include "Game/AI/Action/actionDemoVisibleOff.h"

namespace uking::action {

DemoVisibleOff::DemoVisibleOff(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DemoVisibleOff::~DemoVisibleOff() = default;

bool DemoVisibleOff::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DemoVisibleOff::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DemoVisibleOff::leave_() {
    ksys::act::ai::Action::leave_();
}

void DemoVisibleOff::loadParams_() {}

void DemoVisibleOff::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
