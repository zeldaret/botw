#pragma once

#include "Game/AI/AI/aiCircleMoveInFluid.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CircleMoveInWater : public CircleMoveInFluid {
    SEAD_RTTI_OVERRIDE(CircleMoveInWater, CircleMoveInFluid)
public:
    explicit CircleMoveInWater(const InitArg& arg);
    ~CircleMoveInWater() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xe0
    const float* mAllowMoveWaterDepth_s{};
    // dynamic_param at offset 0xe8
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
