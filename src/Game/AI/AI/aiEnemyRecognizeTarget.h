#pragma once

#include "Game/AI/AI/aiEnemyRecognizeTargetBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyRecognizeTarget : public EnemyRecognizeTargetBase {
    SEAD_RTTI_OVERRIDE(EnemyRecognizeTarget, EnemyRecognizeTargetBase)
public:
    explicit EnemyRecognizeTarget(const InitArg& arg);
    ~EnemyRecognizeTarget() override;

    void loadParams_() override;

protected:
    // map_unit_param at offset 0x128
    sead::SafeString mEquipItem1_m{};
    // map_unit_param at offset 0x138
    sead::SafeString mEquipItem2_m{};
    // static_param at offset 0x148
    const int* mSummonNum_s{};
    // static_param at offset 0x150
    const float* mSummonGrassHeight_s{};
    // static_param at offset 0x158
    const float* mSummonCheckDist_s{};
};

}  // namespace uking::ai
