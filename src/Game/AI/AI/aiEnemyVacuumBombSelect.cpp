#include "Game/AI/AI/aiEnemyVacuumBombSelect.h"

namespace uking::ai {

EnemyVacuumBombSelect::EnemyVacuumBombSelect(const InitArg& arg) : EnemyVacuumBombSelectBase(arg) {}

EnemyVacuumBombSelect::~EnemyVacuumBombSelect() = default;

bool EnemyVacuumBombSelect::init_(sead::Heap* heap) {
    return EnemyVacuumBombSelectBase::init_(heap);
}

void EnemyVacuumBombSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyVacuumBombSelectBase::enter_(params);
}

void EnemyVacuumBombSelect::leave_() {
    EnemyVacuumBombSelectBase::leave_();
}

void EnemyVacuumBombSelect::loadParams_() {
    EnemyVacuumBombSelectBase::loadParams_();
}

}  // namespace uking::ai
