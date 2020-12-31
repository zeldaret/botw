#include "Game/AI/AI/aiEnemyRestraintCheckBattle.h"

namespace uking::ai {

EnemyRestraintCheckBattle::EnemyRestraintCheckBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyRestraintCheckBattle::~EnemyRestraintCheckBattle() = default;

void EnemyRestraintCheckBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyRestraintCheckBattle::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyRestraintCheckBattle::loadParams_() {
    getStaticParam(&mCheckInterval_s, "CheckInterval");
    getStaticParam(&mCheckRandTime_s, "CheckRandTime");
    getStaticParam(&mCheckDist_s, "CheckDist");
    getStaticParam(&mCheckVmin_s, "CheckVmin");
    getStaticParam(&mCheckVmax_s, "CheckVmax");
    getStaticParam(&mCheckAngle_s, "CheckAngle");
    getStaticParam(&mIsResetInterval_s, "IsResetInterval");
}

}  // namespace uking::ai
