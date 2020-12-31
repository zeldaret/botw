#include "Game/AI/AI/aiGuardianMiniBeamAttackMove.h"

namespace uking::ai {

GuardianMiniBeamAttackMove::GuardianMiniBeamAttackMove(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

GuardianMiniBeamAttackMove::~GuardianMiniBeamAttackMove() = default;

void GuardianMiniBeamAttackMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GuardianMiniBeamAttackMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GuardianMiniBeamAttackMove::loadParams_() {
    getStaticParam(&mMoveTime_s, "MoveTime");
    getStaticParam(&mAttackInterval_s, "AttackInterval");
    getStaticParam(&mBeamSpeed_s, "BeamSpeed");
    getStaticParam(&mBaseNode_s, "BaseNode");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mTargetDistOffset_s, "TargetDistOffset");
}

}  // namespace uking::ai
