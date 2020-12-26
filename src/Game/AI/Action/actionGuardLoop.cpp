#include "Game/AI/Action/actionGuardLoop.h"

namespace uking::action {

GuardLoop::GuardLoop(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

GuardLoop::~GuardLoop() = default;

bool GuardLoop::init_(sead::Heap* heap) {
    return ActionWithPosAngReduce::init_(heap);
}

void GuardLoop::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
}

void GuardLoop::leave_() {
    ActionWithPosAngReduce::leave_();
}

void GuardLoop::loadParams_() {
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mAngReduceRatio_s, "AngReduceRatio");
}

void GuardLoop::calc_() {
    ActionWithPosAngReduce::calc_();
}

}  // namespace uking::action
