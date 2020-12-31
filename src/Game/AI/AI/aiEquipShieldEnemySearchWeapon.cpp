#include "Game/AI/AI/aiEquipShieldEnemySearchWeapon.h"

namespace uking::ai {

EquipShieldEnemySearchWeapon::EquipShieldEnemySearchWeapon(const InitArg& arg)
    : UnarmedEnemySearchWeapon(arg) {}

EquipShieldEnemySearchWeapon::~EquipShieldEnemySearchWeapon() = default;

void EquipShieldEnemySearchWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    UnarmedEnemySearchWeapon::enter_(params);
}

void EquipShieldEnemySearchWeapon::leave_() {
    UnarmedEnemySearchWeapon::leave_();
}

void EquipShieldEnemySearchWeapon::loadParams_() {
    UnarmedEnemySearchWeapon::loadParams_();
}

}  // namespace uking::ai
