#include "Game/AI/Action/actionWaitUntilLifeUpDemo.h"

namespace uking::action {

WaitUntilLifeUpDemo::WaitUntilLifeUpDemo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WaitUntilLifeUpDemo::~WaitUntilLifeUpDemo() = default;

bool WaitUntilLifeUpDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaitUntilLifeUpDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WaitUntilLifeUpDemo::leave_() {
    ksys::act::ai::Action::leave_();
}

void WaitUntilLifeUpDemo::loadParams_() {}

void WaitUntilLifeUpDemo::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
