#include "Game/AI/AI/aiWolfLinkChainAttack.h"

namespace uking::ai {

WolfLinkChainAttack::WolfLinkChainAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WolfLinkChainAttack::~WolfLinkChainAttack() = default;

bool WolfLinkChainAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WolfLinkChainAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WolfLinkChainAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WolfLinkChainAttack::loadParams_() {
    getStaticParam(&mNumAttacks_s, "NumAttacks");
    getStaticParam(&mAnimalUnitRate_s, "AnimalUnitRate");
    getStaticParam(&mBeginEndAnimASPlayRate_s, "BeginEndAnimASPlayRate");
    getStaticParam(&mTurnAnimPlayRate_s, "TurnAnimPlayRate");
    getStaticParam(&mAttackAnimPlayRate_s, "AttackAnimPlayRate");
    getStaticParam(&mAttackAnimMinDistance_s, "AttackAnimMinDistance");
    getStaticParam(&mAttackDistanceOffset_s, "AttackDistanceOffset");
    getStaticParam(&mIsInvincible_s, "IsInvincible");
    getStaticParam(&mIsIncrementHitOnMiss_s, "IsIncrementHitOnMiss");
}

}  // namespace uking::ai
