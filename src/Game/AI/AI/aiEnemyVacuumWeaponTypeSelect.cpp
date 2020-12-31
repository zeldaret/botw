#include "Game/AI/AI/aiEnemyVacuumWeaponTypeSelect.h"

namespace uking::ai {

EnemyVacuumWeaponTypeSelect::EnemyVacuumWeaponTypeSelect(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

EnemyVacuumWeaponTypeSelect::~EnemyVacuumWeaponTypeSelect() = default;

bool EnemyVacuumWeaponTypeSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyVacuumWeaponTypeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyVacuumWeaponTypeSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyVacuumWeaponTypeSelect::loadParams_() {
    getStaticParam(&mPartsKey_s, "PartsKey");
}

}  // namespace uking::ai
