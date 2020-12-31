#include "Game/AI/AI/aiEnemyNotice.h"

namespace uking::ai {

EnemyNotice::EnemyNotice(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void EnemyNotice::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyNotice::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyNotice::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mTurnStartAngle_s, "TurnStartAngle");
}

}  // namespace uking::ai
