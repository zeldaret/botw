#include "Game/AI/Action/actionDemoVisibleOn.h"

namespace uking::action {

DemoVisibleOn::DemoVisibleOn(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DemoVisibleOn::~DemoVisibleOn() = default;

bool DemoVisibleOn::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DemoVisibleOn::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DemoVisibleOn::leave_() {
    ksys::act::ai::Action::leave_();
}

void DemoVisibleOn::loadParams_() {}

void DemoVisibleOn::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
