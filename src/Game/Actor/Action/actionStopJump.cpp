#include "Game/Actor/Action/actionStopJump.h"

namespace uking::action {

StopJump::StopJump(const InitArg& arg) : StopBase(arg) {}

StopJump::~StopJump() = default;

bool StopJump::init_(sead::Heap* heap) {
    return StopBase::init_(heap);
}

void StopJump::enter_(ksys::act::ai::InlineParamPack* params) {
    StopBase::enter_(params);
}

void StopJump::leave_() {
    StopBase::leave_();
}

void StopJump::loadParams_() {
    StopBase::loadParams_();
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mJumpLoopAS_s, "JumpLoopAS");
    getStaticParam(&mLandingAS_s, "LandingAS");
}

void StopJump::calc_() {
    StopBase::calc_();
}

}  // namespace uking::action
