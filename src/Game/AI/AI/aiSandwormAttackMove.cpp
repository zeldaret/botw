#include "Game/AI/AI/aiSandwormAttackMove.h"

namespace uking::ai {

SandwormAttackMove::SandwormAttackMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SandwormAttackMove::~SandwormAttackMove() = default;

bool SandwormAttackMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SandwormAttackMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SandwormAttackMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SandwormAttackMove::loadParams_() {
    getStaticParam(&mSecessionDist_s, "SecessionDist");
    getStaticParam(&mAttackAngle_s, "AttackAngle");
    getStaticParam(&mDamageAngle_s, "DamageAngle");
    getStaticParam(&mLostDist_s, "LostDist");
    getStaticParam(&mDamageBaseNode_s, "DamageBaseNode");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
