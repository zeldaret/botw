#include "Game/Actor/AI/aiGuardianMiniBeamAttack.h"

namespace uking::ai {

GuardianMiniBeamAttack::GuardianMiniBeamAttack(const InitArg& arg)
    : GuideBeamAttackEnemyBattle(arg) {}

GuardianMiniBeamAttack::~GuardianMiniBeamAttack() = default;

void GuardianMiniBeamAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    GuideBeamAttackEnemyBattle::enter_(params);
}

void GuardianMiniBeamAttack::leave_() {
    GuideBeamAttackEnemyBattle::leave_();
}

void GuardianMiniBeamAttack::loadParams_() {
    GuideBeamAttackEnemyBattle::loadParams_();
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
