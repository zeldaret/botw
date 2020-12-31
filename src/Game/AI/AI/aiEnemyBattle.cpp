#include "Game/AI/AI/aiEnemyBattle.h"

namespace uking::ai {

EnemyBattle::EnemyBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void EnemyBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyBattle::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyBattle::loadParams_() {
    getStaticParam(&mRetFrmGrdAtkTimer_s, "RetFrmGrdAtkTimer");
    getStaticParam(&mRetFrmGrdAtkPrcTimer_s, "RetFrmGrdAtkPrcTimer");
    getStaticParam(&mRetFrmDmgAtkTimer_s, "RetFrmDmgAtkTimer");
    getStaticParam(&mGlobalNoAtkTime_s, "GlobalNoAtkTime");
    getStaticParam(&mGlobalNoAtkTimeRnd_s, "GlobalNoAtkTimeRnd");
    getStaticParam(&mAttackAngle_s, "AttackAngle");
    getStaticParam(&mAttackIntervalIntensity_s, "AttackIntervalIntensity");
    getStaticParam(&mDisplayCheckRadius_s, "DisplayCheckRadius");
    getStaticParam(&mIsUpdateNoticeState_s, "IsUpdateNoticeState");
    getStaticParam(&mIsCheckLineReachable_s, "IsCheckLineReachable");
}

}  // namespace uking::ai
