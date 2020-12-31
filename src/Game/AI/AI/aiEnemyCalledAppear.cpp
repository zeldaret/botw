#include "Game/AI/AI/aiEnemyCalledAppear.h"

namespace uking::ai {

EnemyCalledAppear::EnemyCalledAppear(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyCalledAppear::~EnemyCalledAppear() = default;

bool EnemyCalledAppear::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyCalledAppear::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyCalledAppear::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyCalledAppear::loadParams_() {}

}  // namespace uking::ai
