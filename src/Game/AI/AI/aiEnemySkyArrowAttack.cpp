#include "Game/AI/AI/aiEnemySkyArrowAttack.h"

namespace uking::ai {

EnemySkyArrowAttack::EnemySkyArrowAttack(const InitArg& arg) : EnemyBaseArrowAttack(arg) {}

EnemySkyArrowAttack::~EnemySkyArrowAttack() = default;

bool EnemySkyArrowAttack::init_(sead::Heap* heap) {
    return EnemyBaseArrowAttack::init_(heap);
}

void EnemySkyArrowAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBaseArrowAttack::enter_(params);
}

void EnemySkyArrowAttack::leave_() {
    EnemyBaseArrowAttack::leave_();
}

void EnemySkyArrowAttack::loadParams_() {
    EnemyBaseArrowAttack::loadParams_();
}

}  // namespace uking::ai
