#include "Game/AI/AI/aiHorseRideEnemyNormal.h"

namespace uking::ai {

HorseRideEnemyNormal::HorseRideEnemyNormal(const InitArg& arg) : EnemyNormal(arg) {}

HorseRideEnemyNormal::~HorseRideEnemyNormal() = default;

bool HorseRideEnemyNormal::init_(sead::Heap* heap) {
    return EnemyNormal::init_(heap);
}

void HorseRideEnemyNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNormal::enter_(params);
}

void HorseRideEnemyNormal::leave_() {
    EnemyNormal::leave_();
}

void HorseRideEnemyNormal::loadParams_() {
    EnemyNormal::loadParams_();
    getStaticParam(&mSightAwarenessScale_s, "SightAwarenessScale");
}

}  // namespace uking::ai
