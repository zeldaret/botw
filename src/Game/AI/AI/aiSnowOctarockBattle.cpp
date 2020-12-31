#include "Game/AI/AI/aiSnowOctarockBattle.h"

namespace uking::ai {

SnowOctarockBattle::SnowOctarockBattle(const InitArg& arg) : EnemyBattle(arg) {}

SnowOctarockBattle::~SnowOctarockBattle() = default;

bool SnowOctarockBattle::init_(sead::Heap* heap) {
    return EnemyBattle::init_(heap);
}

void SnowOctarockBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBattle::enter_(params);
}

void SnowOctarockBattle::leave_() {
    EnemyBattle::leave_();
}

void SnowOctarockBattle::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mVacuumPartsKey_s, "VacuumPartsKey");
    getStaticParam(&mShootActorKey_s, "ShootActorKey");
}

}  // namespace uking::ai
