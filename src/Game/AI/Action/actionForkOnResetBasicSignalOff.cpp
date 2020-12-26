#include "Game/AI/Action/actionForkOnResetBasicSignalOff.h"

namespace uking::action {

ForkOnResetBasicSignalOff::ForkOnResetBasicSignalOff(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkOnResetBasicSignalOff::~ForkOnResetBasicSignalOff() = default;

bool ForkOnResetBasicSignalOff::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkOnResetBasicSignalOff::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkOnResetBasicSignalOff::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkOnResetBasicSignalOff::loadParams_() {}

void ForkOnResetBasicSignalOff::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
