#include "Game/AI/AI/aiEnemyNoticeActiveEnemy.h"

namespace uking::ai {

EnemyNoticeActiveEnemy::EnemyNoticeActiveEnemy(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyNoticeActiveEnemy::~EnemyNoticeActiveEnemy() = default;

bool EnemyNoticeActiveEnemy::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyNoticeActiveEnemy::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyNoticeActiveEnemy::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyNoticeActiveEnemy::loadParams_() {
    getDynamicParam(&mTargetActor_d, "TargetActor");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
