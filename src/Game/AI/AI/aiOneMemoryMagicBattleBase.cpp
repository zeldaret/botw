#include "Game/AI/AI/aiOneMemoryMagicBattleBase.h"

namespace uking::ai {

OneMemoryMagicBattleBase::OneMemoryMagicBattleBase(const InitArg& arg) : EnemyBattle(arg) {}

OneMemoryMagicBattleBase::~OneMemoryMagicBattleBase() = default;

bool OneMemoryMagicBattleBase::init_(sead::Heap* heap) {
    return EnemyBattle::init_(heap);
}

void OneMemoryMagicBattleBase::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBattle::enter_(params);
}

void OneMemoryMagicBattleBase::leave_() {
    EnemyBattle::leave_();
}

void OneMemoryMagicBattleBase::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mEnlargeTime_s, "EnlargeTime");
    getStaticParam(&mAttackRatio_s, "AttackRatio");
    getStaticParam(&mBreathSize_s, "BreathSize");
    getStaticParam(&mMagicName_s, "MagicName");
    getStaticParam(&mMagicPer_s, "MagicPer");
    getStaticParam(&mAttackPowDirect_s, "AttackPowDirect");
}

}  // namespace uking::ai
