#include "Game/AI/AI/aiHorseRideShootingEnemyBattle.h"

namespace uking::ai {

HorseRideShootingEnemyBattle::HorseRideShootingEnemyBattle(const InitArg& arg)
    : ShootingEnemyBattle(arg) {}

HorseRideShootingEnemyBattle::~HorseRideShootingEnemyBattle() = default;

bool HorseRideShootingEnemyBattle::init_(sead::Heap* heap) {
    return ShootingEnemyBattle::init_(heap);
}

void HorseRideShootingEnemyBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    ShootingEnemyBattle::enter_(params);
}

void HorseRideShootingEnemyBattle::leave_() {
    ShootingEnemyBattle::leave_();
}

void HorseRideShootingEnemyBattle::loadParams_() {
    ShootingEnemyBattle::loadParams_();
    getStaticParam(&mTrackTime_s, "TrackTime");
    getStaticParam(&mTrackTimeRand_s, "TrackTimeRand");
    getStaticParam(&mSlowTime_s, "SlowTime");
    getStaticParam(&mSlowTimeRand_s, "SlowTimeRand");
}

}  // namespace uking::ai
