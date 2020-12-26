#include "Game/AI/Action/actionSandwormJumpTackle.h"

namespace uking::action {

SandwormJumpTackle::SandwormJumpTackle(const InitArg& arg) : JumpTackle(arg) {}

SandwormJumpTackle::~SandwormJumpTackle() = default;

bool SandwormJumpTackle::init_(sead::Heap* heap) {
    return JumpTackle::init_(heap);
}

void SandwormJumpTackle::enter_(ksys::act::ai::InlineParamPack* params) {
    JumpTackle::enter_(params);
}

void SandwormJumpTackle::leave_() {
    JumpTackle::leave_();
}

void SandwormJumpTackle::loadParams_() {
    JumpTackle::loadParams_();
    getStaticParam(&mPosReduceRate_s, "PosReduceRate");
    getStaticParam(&mGravityScale_s, "GravityScale");
    getStaticParam(&mAtkColName_s, "AtkColName");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void SandwormJumpTackle::calc_() {
    JumpTackle::calc_();
}

}  // namespace uking::action
