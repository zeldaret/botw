#include "Game/AI/AI/aiEnemyChemicalPowerSelect.h"

namespace uking::ai {

EnemyChemicalPowerSelect::EnemyChemicalPowerSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyChemicalPowerSelect::~EnemyChemicalPowerSelect() = default;

bool EnemyChemicalPowerSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyChemicalPowerSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyChemicalPowerSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyChemicalPowerSelect::loadParams_() {}

}  // namespace uking::ai
