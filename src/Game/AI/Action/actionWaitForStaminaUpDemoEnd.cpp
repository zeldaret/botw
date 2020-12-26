#include "Game/AI/Action/actionWaitForStaminaUpDemoEnd.h"

namespace uking::action {

WaitForStaminaUpDemoEnd::WaitForStaminaUpDemoEnd(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WaitForStaminaUpDemoEnd::~WaitForStaminaUpDemoEnd() = default;

bool WaitForStaminaUpDemoEnd::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaitForStaminaUpDemoEnd::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WaitForStaminaUpDemoEnd::leave_() {
    ksys::act::ai::Action::leave_();
}

void WaitForStaminaUpDemoEnd::loadParams_() {}

void WaitForStaminaUpDemoEnd::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
