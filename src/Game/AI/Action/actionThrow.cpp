#include "Game/AI/Action/actionThrow.h"

namespace uking::action {

Throw::Throw(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

Throw::~Throw() = default;

bool Throw::init_(sead::Heap* heap) {
    return ActionWithPosAngReduce::init_(heap);
}

void Throw::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
}

void Throw::leave_() {
    ActionWithPosAngReduce::leave_();
}

void Throw::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
}

void Throw::calc_() {
    ActionWithPosAngReduce::calc_();
}

}  // namespace uking::action
