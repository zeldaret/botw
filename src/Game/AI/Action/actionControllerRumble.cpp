#include "Game/AI/Action/actionControllerRumble.h"

namespace uking::action {

ControllerRumble::ControllerRumble(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ControllerRumble::~ControllerRumble() = default;

bool ControllerRumble::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ControllerRumble::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ControllerRumble::leave_() {
    ksys::act::ai::Action::leave_();
}

void ControllerRumble::loadParams_() {
    getStaticParam(&mPattern_s, "Pattern");
    getDynamicParam2(&mCount_d, "Count");
}

void ControllerRumble::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
