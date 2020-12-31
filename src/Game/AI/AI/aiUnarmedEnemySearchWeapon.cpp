#include "Game/AI/AI/aiUnarmedEnemySearchWeapon.h"

namespace uking::ai {

UnarmedEnemySearchWeapon::UnarmedEnemySearchWeapon(const InitArg& arg) : UnarmedEnemySearch(arg) {}

UnarmedEnemySearchWeapon::~UnarmedEnemySearchWeapon() = default;

void UnarmedEnemySearchWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    UnarmedEnemySearch::enter_(params);
}

void UnarmedEnemySearchWeapon::leave_() {
    UnarmedEnemySearch::leave_();
}

void UnarmedEnemySearchWeapon::loadParams_() {
    UnarmedEnemySearch::loadParams_();
    getStaticParam(&mEquipItemSearchIdx_s, "EquipItemSearchIdx");
    getStaticParam(&mRepathTime_s, "RepathTime");
    getStaticParam(&mSearchDist_s, "SearchDist");
    getStaticParam(&mSearchAng_s, "SearchAng");
    getStaticParam(&mIsUseSight_s, "IsUseSight");
    getStaticParam(&mLineReachableWeaponDist_s, "LineReachableWeaponDist");
}

}  // namespace uking::ai
