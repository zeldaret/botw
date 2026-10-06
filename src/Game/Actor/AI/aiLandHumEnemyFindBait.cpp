#include "Game/Actor/AI/aiLandHumEnemyFindBait.h"

namespace uking::ai {

LandHumEnemyFindBait::LandHumEnemyFindBait(const InitArg& arg) : NavMove(arg) {}

LandHumEnemyFindBait::~LandHumEnemyFindBait() = default;

void LandHumEnemyFindBait::enter_(ksys::act::ai::InlineParamPack* params) {
    NavMove::enter_(params);
}

void LandHumEnemyFindBait::leave_() {
    NavMove::leave_();
}

void LandHumEnemyFindBait::loadParams_() {
    NavMove::loadParams_();
    getStaticParam(&mRepathTime_s, "RepathTime");
    getDynamicParam(&mTargetBait_d, "TargetBait");
    getDynamicParam(&mIsNotice_d, "IsNotice");
    getStaticParam(&mIsDropWeapon_s, "IsDropWeapon");
    getStaticParam(&mIsValidForceNeck_s, "IsValidForceNeck");
}

}  // namespace uking::ai
