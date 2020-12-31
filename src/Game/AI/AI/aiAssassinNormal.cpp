#include "Game/AI/AI/aiAssassinNormal.h"

namespace uking::ai {

AssassinNormal::AssassinNormal(const InitArg& arg) : LandHumEnemyNormal(arg) {}

AssassinNormal::~AssassinNormal() = default;

bool AssassinNormal::init_(sead::Heap* heap) {
    return LandHumEnemyNormal::init_(heap);
}

void AssassinNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    LandHumEnemyNormal::enter_(params);
}

void AssassinNormal::leave_() {
    LandHumEnemyNormal::leave_();
}

void AssassinNormal::loadParams_() {
    LandHumEnemyNormal::loadParams_();
}

}  // namespace uking::ai
