#include "Game/AI/Action/actionAnimTimingAttackMove.h"

namespace uking::action {

AnimTimingAttackMove::AnimTimingAttackMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AnimTimingAttackMove::~AnimTimingAttackMove() = default;

bool AnimTimingAttackMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AnimTimingAttackMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AnimTimingAttackMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void AnimTimingAttackMove::loadParams_() {
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mMaxSpeed_s, "MaxSpeed");
    getStaticParam(&mIsRound_s, "IsRound");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mRigidBodyName_s, "RigidBodyName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void AnimTimingAttackMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
