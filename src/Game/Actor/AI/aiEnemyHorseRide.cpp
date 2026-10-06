#include "Game/Actor/AI/aiEnemyHorseRide.h"

namespace uking::ai {

EnemyHorseRide::EnemyHorseRide(const InitArg& arg) : RideHorseNonPlayer(arg) {}

EnemyHorseRide::~EnemyHorseRide() = default;

bool EnemyHorseRide::init_(sead::Heap* heap) {
    return RideHorseNonPlayer::init_(heap);
}

void EnemyHorseRide::enter_(ksys::act::ai::InlineParamPack* params) {
    RideHorseNonPlayer::enter_(params);
}

void EnemyHorseRide::leave_() {
    RideHorseNonPlayer::leave_();
}

void EnemyHorseRide::loadParams_() {
    RideHorseNonPlayer::loadParams_();
    getStaticParam(&mUpperBodyASSlot_s, "UpperBodyASSlot");
    getStaticParam(&mLowerBodyASSlot_s, "LowerBodyASSlot");
}

}  // namespace uking::ai
