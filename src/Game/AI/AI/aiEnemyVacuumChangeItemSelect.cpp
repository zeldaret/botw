#include "Game/AI/AI/aiEnemyVacuumChangeItemSelect.h"

namespace uking::ai {

EnemyVacuumChangeItemSelect::EnemyVacuumChangeItemSelect(const InitArg& arg)
    : EnemyVacuumBombSelect(arg) {}

EnemyVacuumChangeItemSelect::~EnemyVacuumChangeItemSelect() = default;

bool EnemyVacuumChangeItemSelect::init_(sead::Heap* heap) {
    return EnemyVacuumBombSelect::init_(heap);
}

void EnemyVacuumChangeItemSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyVacuumBombSelect::enter_(params);
}

void EnemyVacuumChangeItemSelect::leave_() {
    EnemyVacuumBombSelect::leave_();
}

void EnemyVacuumChangeItemSelect::loadParams_() {
    EnemyVacuumBombSelect::loadParams_();
}

}  // namespace uking::ai
