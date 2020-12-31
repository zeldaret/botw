#include "Game/AI/AI/aiEnemyNoticeSoundSensitiveTimer.h"

namespace uking::ai {

EnemyNoticeSoundSensitiveTimer::EnemyNoticeSoundSensitiveTimer(const InitArg& arg)
    : EnemyNoticeSoundSensitive(arg) {}

EnemyNoticeSoundSensitiveTimer::~EnemyNoticeSoundSensitiveTimer() = default;

bool EnemyNoticeSoundSensitiveTimer::init_(sead::Heap* heap) {
    return EnemyNoticeSoundSensitive::init_(heap);
}

void EnemyNoticeSoundSensitiveTimer::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNoticeSoundSensitive::enter_(params);
}

void EnemyNoticeSoundSensitiveTimer::leave_() {
    EnemyNoticeSoundSensitive::leave_();
}

void EnemyNoticeSoundSensitiveTimer::loadParams_() {
    EnemyNoticeSoundSensitive::loadParams_();
    getStaticParam(&mTimer_s, "Timer");
}

}  // namespace uking::ai
