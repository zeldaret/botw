#include "Game/AI/AI/aiEnemyRecognizeTarget.h"

namespace uking::ai {

EnemyRecognizeTarget::EnemyRecognizeTarget(const InitArg& arg) : EnemyRecognizeTargetBase(arg) {}

EnemyRecognizeTarget::~EnemyRecognizeTarget() = default;

void EnemyRecognizeTarget::loadParams_() {
    EnemyRecognizeTargetBase::loadParams_();
    getStaticParam(&mSummonNum_s, "SummonNum");
    getStaticParam(&mSummonGrassHeight_s, "SummonGrassHeight");
    getStaticParam(&mSummonCheckDist_s, "SummonCheckDist");
    getMapUnitParam(&mEquipItem1_m, "EquipItem1");
    getMapUnitParam(&mEquipItem2_m, "EquipItem2");
}

}  // namespace uking::ai
