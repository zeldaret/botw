#include "Game/AI/AI/aiEnemyNoticeSound.h"

namespace uking::ai {

EnemyNoticeSound::EnemyNoticeSound(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyNoticeSound::~EnemyNoticeSound() = default;

void EnemyNoticeSound::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyNoticeSound::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyNoticeSound::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
