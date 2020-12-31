#include "Game/AI/AI/aiEnemyEscapeMove.h"

namespace uking::ai {

EnemyEscapeMove::EnemyEscapeMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyEscapeMove::~EnemyEscapeMove() = default;

bool EnemyEscapeMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyEscapeMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyEscapeMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyEscapeMove::loadParams_() {}

}  // namespace uking::ai
