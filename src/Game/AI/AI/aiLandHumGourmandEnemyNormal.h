#pragma once

#include "Game/AI/AI/aiLandHumEnemyNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LandHumGourmandEnemyNormal : public LandHumEnemyNormal {
    SEAD_RTTI_OVERRIDE(LandHumGourmandEnemyNormal, LandHumEnemyNormal)
public:
    explicit LandHumGourmandEnemyNormal(const InitArg& arg);
    ~LandHumGourmandEnemyNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x400
    const int* mRefindBaitTime_s{};
    // static_param at offset 0x408
    const int* mEatArea_s{};
    // static_param at offset 0x410
    const int* mEatNavType_s{};
    // aitree_variable at offset 0x430
    void* mTargetBaitActorLink_a{};
    // aitree_variable at offset 0x438
    bool* mIsTrgChangeUnderWaterState_a{};
};

}  // namespace uking::ai
