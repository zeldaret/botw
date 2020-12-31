#include "Game/AI/AI/aiLandHumEnemyFindPlayer.h"

namespace uking::ai {

LandHumEnemyFindPlayer::LandHumEnemyFindPlayer(const InitArg& arg) : EnemyBaseFindPlayer(arg) {}

LandHumEnemyFindPlayer::~LandHumEnemyFindPlayer() = default;

void LandHumEnemyFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBaseFindPlayer::enter_(params);
}

void LandHumEnemyFindPlayer::leave_() {
    EnemyBaseFindPlayer::leave_();
}

void LandHumEnemyFindPlayer::loadParams_() {
    EnemyBaseFindPlayer::loadParams_();
    getStaticParam(&mExplosivesAvoidDist_s, "ExplosivesAvoidDist");
    getStaticParam(&mExplosivesAvoidSpeed_s, "ExplosivesAvoidSpeed");
    getStaticParam(&mExplosivesAvoidAng_s, "ExplosivesAvoidAng");
    getStaticParam(&mChemicalSearchDist_s, "ChemicalSearchDist");
    getStaticParam(&mNoSearchDist_s, "NoSearchDist");
    getStaticParam(&mVoltage_s, "Voltage");
    getStaticParam(&mChemicalActionDist_s, "ChemicalActionDist");
    getStaticParam(&mThrowWeaponPer_s, "ThrowWeaponPer");
    getStaticParam(&mThrowWeaponDist_s, "ThrowWeaponDist");
    getStaticParam(&mNoChemSearchWpIdx_s, "NoChemSearchWpIdx");
    getStaticParam(&mNoBurnWaterDepth_s, "NoBurnWaterDepth");
    getStaticParam(&mNearScaffoldDist_s, "NearScaffoldDist");
    getStaticParam(&mClimbVmin_s, "ClimbVmin");
    getStaticParam(&mClimbVmax_s, "ClimbVmax");
    getStaticParam(&mClimbHmax_s, "ClimbHmax");
}

}  // namespace uking::ai
