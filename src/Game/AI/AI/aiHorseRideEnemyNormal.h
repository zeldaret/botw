#pragma once

#include "Game/AI/AI/aiEnemyNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HorseRideEnemyNormal : public EnemyNormal {
    SEAD_RTTI_OVERRIDE(HorseRideEnemyNormal, EnemyNormal)
public:
    explicit HorseRideEnemyNormal(const InitArg& arg);
    ~HorseRideEnemyNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x3d0
    const float* mSightAwarenessScale_s{};
};

}  // namespace uking::ai
