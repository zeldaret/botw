#include "Game/AI/AI/aiEnemyNoticeFearfulLastAttacker.h"

namespace uking::ai {

EnemyNoticeFearfulLastAttacker::EnemyNoticeFearfulLastAttacker(const InitArg& arg)
    : EnemyNoticeTerror(arg) {}

EnemyNoticeFearfulLastAttacker::~EnemyNoticeFearfulLastAttacker() = default;

bool EnemyNoticeFearfulLastAttacker::init_(sead::Heap* heap) {
    return EnemyNoticeTerror::init_(heap);
}

void EnemyNoticeFearfulLastAttacker::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNoticeTerror::enter_(params);
}

void EnemyNoticeFearfulLastAttacker::leave_() {
    EnemyNoticeTerror::leave_();
}

void EnemyNoticeFearfulLastAttacker::loadParams_() {
    EnemyNoticeTerror::loadParams_();
}

}  // namespace uking::ai
