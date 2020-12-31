#include "Game/AI/AI/aiEnemyRoot.h"

namespace uking::ai {

EnemyRoot::EnemyRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyRoot::~EnemyRoot() = default;

bool EnemyRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyRoot::loadParams_() {
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mOutOfWaterOffset_s, "OutOfWaterOffset");
    getStaticParam(&mSpreadDist_s, "SpreadDist");
    getStaticParam(&mSmallSpreadDist_s, "SmallSpreadDist");
    getStaticParam(&mFortressTag_s, "FortressTag");
    getStaticParam(&mIgnoreHell_s, "IgnoreHell");
    getMapUnitParam(&mIsNearCreate_m, "IsNearCreate");
    getMapUnitParam(&mEquipItem1_m, "EquipItem1");
    getMapUnitParam(&mEquipItem2_m, "EquipItem2");
    getMapUnitParam(&mEquipItem3_m, "EquipItem3");
    getMapUnitParam(&mEquipItem4_m, "EquipItem4");
    getMapUnitParam(&mRideHorseName_m, "RideHorseName");
    getAITreeVariable(&mCreateDeadConditionType_a, "CreateDeadConditionType");
    getAITreeVariable(&mForceSealSilentKillCount_a, "ForceSealSilentKillCount");
    getAITreeVariable(&mIsTrgChangeUnderWaterState_a, "IsTrgChangeUnderWaterState");
}

}  // namespace uking::ai
