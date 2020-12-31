#include "Game/AI/AI/aiLandHumEnemyFindBaitWeapon.h"

namespace uking::ai {

LandHumEnemyFindBaitWeapon::LandHumEnemyFindBaitWeapon(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

LandHumEnemyFindBaitWeapon::~LandHumEnemyFindBaitWeapon() = default;

void LandHumEnemyFindBaitWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LandHumEnemyFindBaitWeapon::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LandHumEnemyFindBaitWeapon::loadParams_() {
    getDynamicParam(&mTargetWeapon_d, "TargetWeapon");
}

}  // namespace uking::ai
