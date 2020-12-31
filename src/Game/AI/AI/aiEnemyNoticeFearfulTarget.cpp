#include "Game/AI/AI/aiEnemyNoticeFearfulTarget.h"

namespace uking::ai {

EnemyNoticeFearfulTarget::EnemyNoticeFearfulTarget(const InitArg& arg) : EnemyNoticeTerror(arg) {}

EnemyNoticeFearfulTarget::~EnemyNoticeFearfulTarget() = default;

bool EnemyNoticeFearfulTarget::init_(sead::Heap* heap) {
    return EnemyNoticeTerror::init_(heap);
}

void EnemyNoticeFearfulTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNoticeTerror::enter_(params);
}

void EnemyNoticeFearfulTarget::leave_() {
    EnemyNoticeTerror::leave_();
}

void EnemyNoticeFearfulTarget::loadParams_() {
    EnemyNoticeTerror::loadParams_();
}

}  // namespace uking::ai
