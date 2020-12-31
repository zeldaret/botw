#include "Game/AI/AI/aiEnemyDefaultReaction.h"

namespace uking::ai {

EnemyDefaultReaction::EnemyDefaultReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void EnemyDefaultReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyDefaultReaction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyDefaultReaction::loadParams_() {
    getStaticParam(&mJustGuardTimesMin_s, "JustGuardTimesMin");
    getStaticParam(&mJustGuardTimesMax_s, "JustGuardTimesMax");
    getStaticParam(&mSmallDamageCancelTimes_s, "SmallDamageCancelTimes");
    getStaticParam(&mInComboSmallDamageNoCancel_s, "InComboSmallDamageNoCancel");
}

}  // namespace uking::ai
