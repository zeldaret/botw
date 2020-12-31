#include "Game/AI/AI/aiEnemyRoam.h"

namespace uking::ai {

EnemyRoam::EnemyRoam(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void EnemyRoam::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyRoam::loadParams_() {
    getStaticParam(&mSearchPer_s, "SearchPer");
    getStaticParam(&mTerritoryRadius_s, "TerritoryRadius");
    getStaticParam(&mTerritoryRadiusRnd_s, "TerritoryRadiusRnd");
    getStaticParam(&mMinMoveDist_s, "MinMoveDist");
    getDynamicParam(&mCentralPos_d, "CentralPos");
}

}  // namespace uking::ai
