#include "Game/AI/AI/aiEnemyHide.h"

namespace uking::ai {

EnemyHide::EnemyHide(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyHide::~EnemyHide() = default;

bool EnemyHide::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyHide::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyHide::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyHide::loadParams_() {}

}  // namespace uking::ai
