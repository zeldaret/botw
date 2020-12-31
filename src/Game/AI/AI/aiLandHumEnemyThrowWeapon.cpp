#include "Game/AI/AI/aiLandHumEnemyThrowWeapon.h"

namespace uking::ai {

LandHumEnemyThrowWeapon::LandHumEnemyThrowWeapon(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LandHumEnemyThrowWeapon::~LandHumEnemyThrowWeapon() = default;

void LandHumEnemyThrowWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LandHumEnemyThrowWeapon::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LandHumEnemyThrowWeapon::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mThrowWeaponNearDist_s, "ThrowWeaponNearDist");
    getStaticParam(&mWaitTimeMax_s, "WaitTimeMax");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
