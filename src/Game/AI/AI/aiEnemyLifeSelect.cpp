#include "Game/AI/AI/aiEnemyLifeSelect.h"

namespace uking::ai {

EnemyLifeSelect::EnemyLifeSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyLifeSelect::~EnemyLifeSelect() = default;

bool EnemyLifeSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyLifeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyLifeSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyLifeSelect::loadParams_() {
    getMapUnitParam(&mIsWatchKeeping_m, "IsWatchKeeping");
}

}  // namespace uking::ai
