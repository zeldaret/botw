#include "Game/AI/AI/aiOctarockBattle.h"

namespace uking::ai {

OctarockBattle::OctarockBattle(const InitArg& arg) : ShootingEnemyBattle(arg) {}

OctarockBattle::~OctarockBattle() = default;

bool OctarockBattle::init_(sead::Heap* heap) {
    return ShootingEnemyBattle::init_(heap);
}

void OctarockBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    ShootingEnemyBattle::enter_(params);
}

void OctarockBattle::leave_() {
    ShootingEnemyBattle::leave_();
}

void OctarockBattle::loadParams_() {
    ShootingEnemyBattle::loadParams_();
    getStaticParam(&mActorDisplayRadius_s, "ActorDisplayRadius");
    getStaticParam(&mAttackDistMin_s, "AttackDistMin");
    getStaticParam(&mIsAttackOnlyOutScreen_s, "IsAttackOnlyOutScreen");
    getStaticParam(&mIsHideMode_s, "IsHideMode");
    getStaticParam(&mIsFirstAttackIntervalZero_s, "IsFirstAttackIntervalZero");
    getStaticParam(&mIsLostAttack_s, "IsLostAttack");
    getStaticParam(&mShootActorKey_s, "ShootActorKey");
    getStaticParam(&mVacuumPartsKey_s, "VacuumPartsKey");
}

}  // namespace uking::ai
