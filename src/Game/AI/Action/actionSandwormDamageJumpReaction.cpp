#include "Game/AI/Action/actionSandwormDamageJumpReaction.h"

namespace uking::action {

SandwormDamageJumpReaction::SandwormDamageJumpReaction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SandwormDamageJumpReaction::~SandwormDamageJumpReaction() = default;

bool SandwormDamageJumpReaction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SandwormDamageJumpReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SandwormDamageJumpReaction::leave_() {
    ksys::act::ai::Action::leave_();
}

void SandwormDamageJumpReaction::loadParams_() {
    getStaticParam(&mTargetSandOffset_s, "TargetSandOffset");
    getStaticParam(&mSandOffsetSpeed_s, "SandOffsetSpeed");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mReduceGravityRate_s, "ReduceGravityRate");
    getStaticParam(&mReduceRotRate_s, "ReduceRotRate");
    getStaticParam(&mWaitASFinish_s, "WaitASFinish");
    getStaticParam(&mWaitSandOffset_s, "WaitSandOffset");
    getStaticParam(&mASName_s, "ASName");
}

void SandwormDamageJumpReaction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
