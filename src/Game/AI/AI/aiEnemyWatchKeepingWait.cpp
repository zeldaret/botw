#include "Game/AI/AI/aiEnemyWatchKeepingWait.h"

namespace uking::ai {

EnemyWatchKeepingWait::EnemyWatchKeepingWait(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyWatchKeepingWait::~EnemyWatchKeepingWait() = default;

bool EnemyWatchKeepingWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyWatchKeepingWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyWatchKeepingWait::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyWatchKeepingWait::loadParams_() {
    getStaticParam(&mIdleCheckMin_s, "IdleCheckMin");
    getStaticParam(&mIdleCheckMax_s, "IdleCheckMax");
    getStaticParam(&mIdlePer_s, "IdlePer");
    getMapUnitParam(&mRotAngle_m, "RotAngle");
    getMapUnitParam(&mWaitTime_m, "WaitTime");
}

}  // namespace uking::ai
