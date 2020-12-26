#include "Game/AI/Action/actionDemoSweep.h"

namespace uking::action {

DemoSweep::DemoSweep(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DemoSweep::~DemoSweep() = default;

bool DemoSweep::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DemoSweep::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DemoSweep::leave_() {
    ksys::act::ai::Action::leave_();
}

void DemoSweep::loadParams_() {
    getDynamicParam(&mDynScalingTime_d, "DynScalingTime");
}

void DemoSweep::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
