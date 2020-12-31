#include "Game/AI/AI/aiAssassinFieldShooterBattleBase.h"

namespace uking::ai {

AssassinFieldShooterBattleBase::AssassinFieldShooterBattleBase(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

AssassinFieldShooterBattleBase::~AssassinFieldShooterBattleBase() = default;

bool AssassinFieldShooterBattleBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AssassinFieldShooterBattleBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void AssassinFieldShooterBattleBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AssassinFieldShooterBattleBase::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mTiredTime_s, "TiredTime");
    getStaticParam(&mWarpDistNear_s, "WarpDistNear");
    getStaticParam(&mWarpDistFar_s, "WarpDistFar");
    getStaticParam(&mTerritoryDist_s, "TerritoryDist");
    getStaticParam(&mTiredGrHeight_s, "TiredGrHeight");
    getStaticParam(&mIntervalIntensity_s, "IntervalIntensity");
}

}  // namespace uking::ai
