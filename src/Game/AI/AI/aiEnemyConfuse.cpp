#include "Game/AI/AI/aiEnemyConfuse.h"

namespace uking::ai {

EnemyConfuse::EnemyConfuse(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyConfuse::~EnemyConfuse() = default;

bool EnemyConfuse::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyConfuse::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyConfuse::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyConfuse::loadParams_() {
    getStaticParam(&mConfuseTime_s, "ConfuseTime");
}

}  // namespace uking::ai
