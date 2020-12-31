#include "Game/AI/AI/aiAssassinBattle.h"

namespace uking::ai {

AssassinBattle::AssassinBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AssassinBattle::~AssassinBattle() = default;

bool AssassinBattle::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AssassinBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void AssassinBattle::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AssassinBattle::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mTiredTime_s, "TiredTime");
    getStaticParam(&mWarpDist_s, "WarpDist");
    getStaticParam(&mBattleBaseDist_s, "BattleBaseDist");
    getStaticParam(&mFirstAttackResetDist_s, "FirstAttackResetDist");
    getStaticParam(&mBattleDistOutDist_s, "BattleDistOutDist");
    getStaticParam(&mFirstAttackAngle_s, "FirstAttackAngle");
    getStaticParam(&mTiredDist_s, "TiredDist");
    getStaticParam(&mFirstAttackDist_s, "FirstAttackDist");
    getStaticParam(&mNearTiredOffset_s, "NearTiredOffset");
    getMapUnitParam(&mTerritoryArea_m, "TerritoryArea");
}

}  // namespace uking::ai
