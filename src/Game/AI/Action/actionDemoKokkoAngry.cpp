#include "Game/AI/Action/actionDemoKokkoAngry.h"

namespace uking::action {

DemoKokkoAngry::DemoKokkoAngry(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DemoKokkoAngry::~DemoKokkoAngry() = default;

bool DemoKokkoAngry::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DemoKokkoAngry::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DemoKokkoAngry::leave_() {
    ksys::act::ai::Action::leave_();
}

void DemoKokkoAngry::loadParams_() {
    getStaticParam(&mWaitTime_s, "WaitTime");
}

void DemoKokkoAngry::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
