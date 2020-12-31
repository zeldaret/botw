#include "Game/AI/AI/aiEnemyWarnNoticeEndChase.h"

namespace uking::ai {

EnemyWarnNoticeEndChase::EnemyWarnNoticeEndChase(const InitArg& arg) : EnemyWarnNoticeSelect(arg) {}

EnemyWarnNoticeEndChase::~EnemyWarnNoticeEndChase() = default;

bool EnemyWarnNoticeEndChase::init_(sead::Heap* heap) {
    return EnemyWarnNoticeSelect::init_(heap);
}

void EnemyWarnNoticeEndChase::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyWarnNoticeSelect::enter_(params);
}

void EnemyWarnNoticeEndChase::leave_() {
    EnemyWarnNoticeSelect::leave_();
}

void EnemyWarnNoticeEndChase::loadParams_() {
    EnemyWarnNoticeSelect::loadParams_();
}

}  // namespace uking::ai
