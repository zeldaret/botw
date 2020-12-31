#include "Game/AI/AI/aiMiniBeamAttack.h"

namespace uking::ai {

MiniBeamAttack::MiniBeamAttack(const InitArg& arg) : BreathAttackEnemyBattle(arg) {}

MiniBeamAttack::~MiniBeamAttack() = default;

bool MiniBeamAttack::init_(sead::Heap* heap) {
    return BreathAttackEnemyBattle::init_(heap);
}

void MiniBeamAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    BreathAttackEnemyBattle::enter_(params);
}

void MiniBeamAttack::leave_() {
    BreathAttackEnemyBattle::leave_();
}

void MiniBeamAttack::loadParams_() {
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
