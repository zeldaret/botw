#include "Game/AI/AI/aiEnemyFindHorseRideTarget.h"

namespace uking::ai {

EnemyFindHorseRideTarget::EnemyFindHorseRideTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyFindHorseRideTarget::~EnemyFindHorseRideTarget() = default;

bool EnemyFindHorseRideTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyFindHorseRideTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyFindHorseRideTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyFindHorseRideTarget::loadParams_() {
    getStaticParam(&mSurpriseAttackPer_s, "SurpriseAttackPer");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mLostTimer_s, "LostTimer");
    getStaticParam(&mChaseTime_s, "ChaseTime");
    getStaticParam(&mSurpriseAttackRange_s, "SurpriseAttackRange");
    getStaticParam(&mAttackRange_s, "AttackRange");
    getStaticParam(&mAttackVMin_s, "AttackVMin");
    getStaticParam(&mAttackVMax_s, "AttackVMax");
    getStaticParam(&mLostVMin_s, "LostVMin");
    getStaticParam(&mLostVMax_s, "LostVMax");
    getStaticParam(&mLostRange_s, "LostRange");
    getStaticParam(&mAttackTargetSpeed_s, "AttackTargetSpeed");
    getStaticParam(&mReChaseDist_s, "ReChaseDist");
}

}  // namespace uking::ai
