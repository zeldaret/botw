#include "Game/AI/AI/aiLandHumEnemyFindBait.h"

namespace uking::ai {

LandHumEnemyFindBait::LandHumEnemyFindBait(const InitArg& arg) : UnarmedEnemySearch(arg) {}

LandHumEnemyFindBait::~LandHumEnemyFindBait() = default;

void LandHumEnemyFindBait::enter_(ksys::act::ai::InlineParamPack* params) {
    UnarmedEnemySearch::enter_(params);
}

void LandHumEnemyFindBait::leave_() {
    UnarmedEnemySearch::leave_();
}

void LandHumEnemyFindBait::loadParams_() {
    UnarmedEnemySearch::loadParams_();
    getStaticParam(&mRepathTime_s, "RepathTime");
    getDynamicParam(&mTargetBait_d, "TargetBait");
    getDynamicParam(&mIsNotice_d, "IsNotice");
    getStaticParam(&mIsDropWeapon_s, "IsDropWeapon");
    getStaticParam(&mIsValidForceNeck_s, "IsValidForceNeck");
}

}  // namespace uking::ai
