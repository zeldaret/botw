#include "Game/AI/Action/actionJumpMove.h"

namespace uking::action {

JumpMove::JumpMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

JumpMove::~JumpMove() = default;

bool JumpMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void JumpMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void JumpMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void JumpMove::loadParams_() {
    getStaticParam(&mPreJumpWait_s, "PreJumpWait");
    getStaticParam(&mMaxMoveSpeed_s, "MaxMoveSpeed");
    getStaticParam(&mMinMoveSpeed_s, "MinMoveSpeed");
    getStaticParam(&mRandAngleLimit_s, "RandAngleLimit");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mASKey_s, "ASKey");
}

void JumpMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
