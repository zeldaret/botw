#include "Game/AI/Action/actionWaitUntilMapOpenDemoEnd.h"

namespace uking::action {

WaitUntilMapOpenDemoEnd::WaitUntilMapOpenDemoEnd(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WaitUntilMapOpenDemoEnd::~WaitUntilMapOpenDemoEnd() = default;

bool WaitUntilMapOpenDemoEnd::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaitUntilMapOpenDemoEnd::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WaitUntilMapOpenDemoEnd::leave_() {
    ksys::act::ai::Action::leave_();
}

void WaitUntilMapOpenDemoEnd::loadParams_() {}

void WaitUntilMapOpenDemoEnd::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
