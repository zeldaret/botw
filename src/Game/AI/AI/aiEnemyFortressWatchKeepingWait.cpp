#include "Game/AI/AI/aiEnemyFortressWatchKeepingWait.h"

namespace uking::ai {

EnemyFortressWatchKeepingWait::EnemyFortressWatchKeepingWait(const InitArg& arg)
    : EnemyWatchKeepingWait(arg) {}

EnemyFortressWatchKeepingWait::~EnemyFortressWatchKeepingWait() = default;

bool EnemyFortressWatchKeepingWait::init_(sead::Heap* heap) {
    return EnemyWatchKeepingWait::init_(heap);
}

void EnemyFortressWatchKeepingWait::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyWatchKeepingWait::enter_(params);
}

void EnemyFortressWatchKeepingWait::leave_() {
    EnemyWatchKeepingWait::leave_();
}

void EnemyFortressWatchKeepingWait::loadParams_() {
    EnemyWatchKeepingWait::loadParams_();
    // FIXME: CALL sub @ 0x7100392230
}

}  // namespace uking::ai
