#include "Game/AI/AI/aiEnemyMoveBattle.h"

namespace uking::ai {

EnemyMoveBattle::EnemyMoveBattle(const InitArg& arg) : EnemyBattle(arg) {}

EnemyMoveBattle::~EnemyMoveBattle() = default;

void EnemyMoveBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBattle::enter_(params);
}

void EnemyMoveBattle::leave_() {
    EnemyBattle::leave_();
}

void EnemyMoveBattle::loadParams_() {
    EnemyBattle::loadParams_();
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mLimitMoveTime_s, "LimitMoveTime");
    getStaticParam(&mMoveDist_s, "MoveDist");
}

}  // namespace uking::ai
