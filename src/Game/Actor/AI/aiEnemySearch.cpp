#include "Game/Actor/AI/aiEnemySearch.h"

namespace uking::ai {

EnemySearch::EnemySearch(const InitArg& arg) : NavMove(arg) {}

EnemySearch::~EnemySearch() = default;

void EnemySearch::enter_(ksys::act::ai::InlineParamPack* params) {
    NavMove::enter_(params);
}

void EnemySearch::leave_() {
    NavMove::leave_();
}

void EnemySearch::loadParams_() {
    NavMove::loadParams_();
    getStaticParam(&mEquipItemSearchIdx_s, "EquipItemSearchIdx");
    getStaticParam(&mRepathTime_s, "RepathTime");
    getStaticParam(&mSearchDist_s, "SearchDist");
    getStaticParam(&mSearchAng_s, "SearchAng");
    getStaticParam(&mIsUseSight_s, "IsUseSight");
    getStaticParam(&mLineReachableWeaponDist_s, "LineReachableWeaponDist");
}

}  // namespace uking::ai
