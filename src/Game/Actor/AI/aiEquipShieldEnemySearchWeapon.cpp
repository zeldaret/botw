#include "Game/Actor/AI/aiEquipShieldEnemySearchWeapon.h"

namespace uking::ai {

EquipShieldEnemySearchWeapon::EquipShieldEnemySearchWeapon(const InitArg& arg) : EnemySearch(arg) {}

EquipShieldEnemySearchWeapon::~EquipShieldEnemySearchWeapon() = default;

void EquipShieldEnemySearchWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemySearch::enter_(params);
}

void EquipShieldEnemySearchWeapon::leave_() {
    EnemySearch::leave_();
}

void EquipShieldEnemySearchWeapon::loadParams_() {
    EnemySearch::loadParams_();
}

}  // namespace uking::ai
