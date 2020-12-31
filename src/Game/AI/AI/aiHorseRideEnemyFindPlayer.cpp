#include "Game/AI/AI/aiHorseRideEnemyFindPlayer.h"

namespace uking::ai {

HorseRideEnemyFindPlayer::HorseRideEnemyFindPlayer(const InitArg& arg) : EnemyBaseFindPlayer(arg) {}

HorseRideEnemyFindPlayer::~HorseRideEnemyFindPlayer() = default;

bool HorseRideEnemyFindPlayer::init_(sead::Heap* heap) {
    return EnemyBaseFindPlayer::init_(heap);
}

void HorseRideEnemyFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBaseFindPlayer::enter_(params);
}

void HorseRideEnemyFindPlayer::leave_() {
    EnemyBaseFindPlayer::leave_();
}

void HorseRideEnemyFindPlayer::loadParams_() {
    EnemyBaseFindPlayer::loadParams_();
}

}  // namespace uking::ai
