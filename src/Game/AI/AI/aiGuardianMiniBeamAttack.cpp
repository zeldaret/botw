#include "Game/AI/AI/aiGuardianMiniBeamAttack.h"

namespace uking::ai {

GuardianMiniBeamAttack::GuardianMiniBeamAttack(const InitArg& arg) : MiniBeamAttack(arg) {}

GuardianMiniBeamAttack::~GuardianMiniBeamAttack() = default;

void GuardianMiniBeamAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    MiniBeamAttack::enter_(params);
}

void GuardianMiniBeamAttack::leave_() {
    MiniBeamAttack::leave_();
}

void GuardianMiniBeamAttack::loadParams_() {
    MiniBeamAttack::loadParams_();
    getStaticParam(&mHeadNodeName_s, "HeadNodeName");
    getStaticParam(&mAttackInterval_s, "AttackInterval");
    getStaticParam(&mEndShaderASFrame_s, "EndShaderASFrame");
    getStaticParam(&mLoopShaderASName_s, "LoopShaderASName");
    getStaticParam(&mEndShaderASName_s, "EndShaderASName");
    getStaticParam(&mPreLaunchEffectName_s, "PreLaunchEffectName");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mIsFinalBattle_s, "IsFinalBattle");
    getStaticParam(&mInDirAngle_s, "InDirAngle");
}

}  // namespace uking::ai
