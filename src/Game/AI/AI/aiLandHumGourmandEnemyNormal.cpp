#include "Game/AI/AI/aiLandHumGourmandEnemyNormal.h"

namespace uking::ai {

LandHumGourmandEnemyNormal::LandHumGourmandEnemyNormal(const InitArg& arg)
    : LandHumEnemyNormal(arg) {}

LandHumGourmandEnemyNormal::~LandHumGourmandEnemyNormal() = default;

bool LandHumGourmandEnemyNormal::init_(sead::Heap* heap) {
    return LandHumEnemyNormal::init_(heap);
}

void LandHumGourmandEnemyNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    LandHumEnemyNormal::enter_(params);
}

void LandHumGourmandEnemyNormal::leave_() {
    LandHumEnemyNormal::leave_();
}

void LandHumGourmandEnemyNormal::loadParams_() {
    LandHumEnemyNormal::loadParams_();
    getStaticParam(&mRefindBaitTime_s, "RefindBaitTime");
    getStaticParam(&mEatArea_s, "EatArea");
    getStaticParam(&mEatNavType_s, "EatNavType");
    getAITreeVariable(&mTargetBaitActorLink_a, "TargetBaitActorLink");
    getAITreeVariable(&mIsTrgChangeUnderWaterState_a, "IsTrgChangeUnderWaterState");
}

}  // namespace uking::ai
