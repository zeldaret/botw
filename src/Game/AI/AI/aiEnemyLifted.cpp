#include "Game/AI/AI/aiEnemyLifted.h"

namespace uking::ai {

EnemyLifted::EnemyLifted(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyLifted::~EnemyLifted() = default;

bool EnemyLifted::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyLifted::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyLifted::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyLifted::loadParams_() {}

}  // namespace uking::ai
