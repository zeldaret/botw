#include "Game/AI/Action/actionJumpToTarget.h"

namespace uking::action {

JumpToTarget::JumpToTarget(const InitArg& arg) : JumpTo(arg) {}

JumpToTarget::~JumpToTarget() = default;

bool JumpToTarget::init_(sead::Heap* heap) {
    return JumpTo::init_(heap);
}

void JumpToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    JumpTo::enter_(params);
}

void JumpToTarget::leave_() {
    JumpTo::leave_();
}

void JumpToTarget::loadParams_() {
    JumpTo::loadParams_();
    getStaticParam(&mPreJumpAS_s, "PreJumpAS");
    getStaticParam(&mJumpAS_s, "JumpAS");
    getStaticParam(&mLandAS_s, "LandAS");
}

void JumpToTarget::calc_() {
    JumpTo::calc_();
}

}  // namespace uking::action
