#include "Game/Actor/AI/aiAssassinShooterBattle.h"

namespace uking::ai {

AssassinShooterBattle::AssassinShooterBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AssassinShooterBattle::~AssassinShooterBattle() = default;

bool AssassinShooterBattle::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AssassinShooterBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void AssassinShooterBattle::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AssassinShooterBattle::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mTiredTime_s, "TiredTime");
    getStaticParam(&mWarpDistNear_s, "WarpDistNear");
    getStaticParam(&mWarpDistFar_s, "WarpDistFar");
    getStaticParam(&mTerritoryDist_s, "TerritoryDist");
    getStaticParam(&mTiredGrHeight_s, "TiredGrHeight");
    getStaticParam(&mIntervalIntensity_s, "IntervalIntensity");
}

}  // namespace uking::ai
