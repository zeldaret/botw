#include "Game/AI/AI/aiEnemyHorseRide.h"

namespace uking::ai {

EnemyHorseRide::EnemyHorseRide(const InitArg& arg) : NonPlayerHorseRide(arg) {}

EnemyHorseRide::~EnemyHorseRide() = default;

bool EnemyHorseRide::init_(sead::Heap* heap) {
    return NonPlayerHorseRide::init_(heap);
}

void EnemyHorseRide::enter_(ksys::act::ai::InlineParamPack* params) {
    NonPlayerHorseRide::enter_(params);
}

void EnemyHorseRide::leave_() {
    NonPlayerHorseRide::leave_();
}

void EnemyHorseRide::loadParams_() {
    NonPlayerHorseRide::loadParams_();
    getStaticParam(&mUpperBodyASSlot_s, "UpperBodyASSlot");
    getStaticParam(&mLowerBodyASSlot_s, "LowerBodyASSlot");
}

}  // namespace uking::ai
