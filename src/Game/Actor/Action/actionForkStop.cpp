#include "Game/Actor/Action/actionForkStop.h"

namespace uking::action {

ForkStop::ForkStop(const InitArg& arg) : StopBase(arg) {}

ForkStop::~ForkStop() = default;

bool ForkStop::init_(sead::Heap* heap) {
    return StopBase::init_(heap);
}

void ForkStop::enter_(ksys::act::ai::InlineParamPack* params) {
    StopBase::enter_(params);
}

void ForkStop::leave_() {
    StopBase::leave_();
}

void ForkStop::loadParams_() {
    StopBase::loadParams_();
}

void ForkStop::calc_() {
    StopBase::calc_();
}

}  // namespace uking::action
