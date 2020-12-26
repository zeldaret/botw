#include "Game/AI/Action/actionStopJump.h"

namespace uking::action {

StopJump::StopJump(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

StopJump::~StopJump() = default;

bool StopJump::init_(sead::Heap* heap) {
    return ActionWithPosAngReduce::init_(heap);
}

void StopJump::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
}

void StopJump::leave_() {
    ActionWithPosAngReduce::leave_();
}

void StopJump::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mJumpLoopAS_s, "JumpLoopAS");
    getStaticParam(&mLandingAS_s, "LandingAS");
}

void StopJump::calc_() {
    ActionWithPosAngReduce::calc_();
}

}  // namespace uking::action
