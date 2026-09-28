#include "Game/Actor/AI/aiGuideBeamAttackEnemyBattle.h"

namespace uking::ai {

GuideBeamAttackEnemyBattle::GuideBeamAttackEnemyBattle(const InitArg& arg)
    : BreathAttackEnemyBattle(arg) {}

GuideBeamAttackEnemyBattle::~GuideBeamAttackEnemyBattle() = default;

bool GuideBeamAttackEnemyBattle::init_(sead::Heap* heap) {
    return BreathAttackEnemyBattle::init_(heap);
}

void GuideBeamAttackEnemyBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    BreathAttackEnemyBattle::enter_(params);
}

void GuideBeamAttackEnemyBattle::leave_() {
    BreathAttackEnemyBattle::leave_();
}

void GuideBeamAttackEnemyBattle::loadParams_() {
    BreathAttackEnemyBattle::loadParams_();
    getStaticParam(&mFluctuationRange_s, "FluctuationRange");
    getStaticParam(&mFluctuationSpan_s, "FluctuationSpan");
    getStaticParam(&mTargetOffsetY_s, "TargetOffsetY");
    getStaticParam(&mNodeName_s, "NodeName");
    getStaticParam(&mIsValidGuide_s, "IsValidGuide");
    getStaticParam(&mIsIgnoreSmallHit_s, "IsIgnoreSmallHit");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mAimEffectName_s, "AimEffectName");
}

}  // namespace uking::ai
