#include "Game/AI/Action/actionWaitForKeyInput.h"

namespace uking::action {

WaitForKeyInput::WaitForKeyInput(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WaitForKeyInput::~WaitForKeyInput() = default;

bool WaitForKeyInput::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaitForKeyInput::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WaitForKeyInput::leave_() {
    ksys::act::ai::Action::leave_();
}

void WaitForKeyInput::loadParams_() {
    getDynamicParam(&mValidInput_d, "ValidInput");
}

void WaitForKeyInput::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
