#pragma once

#include "Game/AI/AI/aiEnemyRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AirOctaState : public EnemyRoot {
    SEAD_RTTI_OVERRIDE(AirOctaState, EnemyRoot)
public:
    explicit AirOctaState(const InitArg& arg);
    ~AirOctaState() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x1d8
    const float* mRopeGravityFactor_s{};
    // static_param at offset 0x1e0
    const float* mBalloonMassRatio_s{};
    // static_param at offset 0x1e8
    const float* mWindForceScale_s{};
    // aitree_variable at offset 0x1f0
    void* mAirOctaDataMgr_a{};
};

}  // namespace uking::ai
