#include "Game/Actor/Action/actionSandwormTackleMove.h"

namespace uking::action {

SandwormTackleMove::SandwormTackleMove(const InitArg& arg) : TackleAttack(arg) {}

SandwormTackleMove::~SandwormTackleMove() = default;

bool SandwormTackleMove::init_(sead::Heap* heap) {
    return TackleAttack::init_(heap);
}

void SandwormTackleMove::enter_(ksys::act::ai::InlineParamPack* params) {
    TackleAttack::enter_(params);
}

void SandwormTackleMove::leave_() {
    TackleAttack::leave_();
}

void SandwormTackleMove::loadParams_() {
    TackleAttack::loadParams_();
    getStaticParam(&mTargetSandOffset_s, "TargetSandOffset");
    getStaticParam(&mSandOffsetSpeed_s, "SandOffsetSpeed");
    getStaticParam(&mEatRadius_s, "EatRadius");
    getStaticParam(&mEatNode_s, "EatNode");
    getStaticParam(&mEatOffset_s, "EatOffset");
}

void SandwormTackleMove::calc_() {
    TackleAttack::calc_();
}

}  // namespace uking::action
