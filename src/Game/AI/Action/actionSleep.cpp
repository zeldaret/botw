#include "Game/AI/Action/actionSleep.h"

namespace uking::action {

Sleep::Sleep(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

Sleep::~Sleep() = default;

bool Sleep::init_(sead::Heap* heap) {
    return ActionWithPosAngReduce::init_(heap);
}

void Sleep::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
}

void Sleep::leave_() {
    ActionWithPosAngReduce::leave_();
}

void Sleep::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
}

void Sleep::calc_() {
    ActionWithPosAngReduce::calc_();
}

}  // namespace uking::action
