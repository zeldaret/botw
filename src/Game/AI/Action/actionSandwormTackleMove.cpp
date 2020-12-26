#include "Game/AI/Action/actionSandwormTackleMove.h"

namespace uking::action {

SandwormTackleMove::SandwormTackleMove(const InitArg& arg) : AtkTackleMove(arg) {}

SandwormTackleMove::~SandwormTackleMove() = default;

bool SandwormTackleMove::init_(sead::Heap* heap) {
    return AtkTackleMove::init_(heap);
}

void SandwormTackleMove::enter_(ksys::act::ai::InlineParamPack* params) {
    AtkTackleMove::enter_(params);
}

void SandwormTackleMove::leave_() {
    AtkTackleMove::leave_();
}

void SandwormTackleMove::loadParams_() {
    AtkTackleMove::loadParams_();
    getStaticParam(&mTargetSandOffset_s, "TargetSandOffset");
    getStaticParam(&mSandOffsetSpeed_s, "SandOffsetSpeed");
    getStaticParam(&mEatRadius_s, "EatRadius");
    getStaticParam(&mEatNode_s, "EatNode");
    getStaticParam(&mEatOffset_s, "EatOffset");
}

void SandwormTackleMove::calc_() {
    AtkTackleMove::calc_();
}

}  // namespace uking::action
