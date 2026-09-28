#include "Game/Actor/AI/aiMagicBattle.h"

namespace uking::ai {

MagicBattle::MagicBattle(const InitArg& arg) : EnemyBattle(arg) {}

MagicBattle::~MagicBattle() = default;

bool MagicBattle::init_(sead::Heap* heap) {
    return EnemyBattle::init_(heap);
}

void MagicBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBattle::enter_(params);
}

void MagicBattle::leave_() {
    EnemyBattle::leave_();
}

void MagicBattle::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mEnlargeTime_s, "EnlargeTime");
    getStaticParam(&mAttackRatio_s, "AttackRatio");
    getStaticParam(&mBreathSize_s, "BreathSize");
    getStaticParam(&mMagicName_s, "MagicName");
    getStaticParam(&mMagicPer_s, "MagicPer");
    getStaticParam(&mAttackPowDirect_s, "AttackPowDirect");
}

}  // namespace uking::ai
