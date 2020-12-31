#include "Game/AI/AI/aiEnemyMoveToGround.h"

namespace uking::ai {

EnemyMoveToGround::EnemyMoveToGround(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyMoveToGround::~EnemyMoveToGround() = default;

bool EnemyMoveToGround::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyMoveToGround::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyMoveToGround::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyMoveToGround::loadParams_() {
    getStaticParam(&mRetryTime_s, "RetryTime");
    getStaticParam(&mAreaThreshold_s, "AreaThreshold");
    getStaticParam(&mSearchRadius_s, "SearchRadius");
}

}  // namespace uking::ai
