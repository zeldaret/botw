#include "Game/AI/AI/aiHorseRideShooterFindPlayer.h"

namespace uking::ai {

HorseRideShooterFindPlayer::HorseRideShooterFindPlayer(const InitArg& arg)
    : SimpleShootingEnemyFindPlayer(arg) {}

HorseRideShooterFindPlayer::~HorseRideShooterFindPlayer() = default;

bool HorseRideShooterFindPlayer::init_(sead::Heap* heap) {
    return SimpleShootingEnemyFindPlayer::init_(heap);
}

void HorseRideShooterFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    SimpleShootingEnemyFindPlayer::enter_(params);
}

void HorseRideShooterFindPlayer::leave_() {
    SimpleShootingEnemyFindPlayer::leave_();
}

void HorseRideShooterFindPlayer::loadParams_() {
    SimpleShootingEnemyFindPlayer::loadParams_();
}

}  // namespace uking::ai
