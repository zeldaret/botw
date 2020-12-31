#include "Game/AI/AI/aiEnemyChaseTargetAndAction.h"

namespace uking::ai {

EnemyChaseTargetAndAction::EnemyChaseTargetAndAction(const InitArg& arg)
    : UnarmedEnemySearch(arg) {}

EnemyChaseTargetAndAction::~EnemyChaseTargetAndAction() = default;

void EnemyChaseTargetAndAction::enter_(ksys::act::ai::InlineParamPack* params) {
    UnarmedEnemySearch::enter_(params);
}

void EnemyChaseTargetAndAction::leave_() {
    UnarmedEnemySearch::leave_();
}

void EnemyChaseTargetAndAction::loadParams_() {
    UnarmedEnemySearch::loadParams_();
    getStaticParam(&mRepathTime_s, "RepathTime");
    getStaticParam(&mLostDist_s, "LostDist");
    getStaticParam(&mLostSpeed_s, "LostSpeed");
    getStaticParam(&mLostAng_s, "LostAng");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai
