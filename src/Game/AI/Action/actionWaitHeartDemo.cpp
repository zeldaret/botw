#include "Game/AI/Action/actionWaitHeartDemo.h"

namespace uking::action {

WaitHeartDemo::WaitHeartDemo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WaitHeartDemo::~WaitHeartDemo() = default;

bool WaitHeartDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaitHeartDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WaitHeartDemo::leave_() {
    ksys::act::ai::Action::leave_();
}

void WaitHeartDemo::loadParams_() {}

void WaitHeartDemo::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
