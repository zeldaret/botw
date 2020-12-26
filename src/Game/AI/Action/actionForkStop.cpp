#include "Game/AI/Action/actionForkStop.h"

namespace uking::action {

ForkStop::ForkStop(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

ForkStop::~ForkStop() = default;

bool ForkStop::init_(sead::Heap* heap) {
    return ActionWithPosAngReduce::init_(heap);
}

void ForkStop::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
}

void ForkStop::leave_() {
    ActionWithPosAngReduce::leave_();
}

void ForkStop::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
}

void ForkStop::calc_() {
    ActionWithPosAngReduce::calc_();
}

}  // namespace uking::action
