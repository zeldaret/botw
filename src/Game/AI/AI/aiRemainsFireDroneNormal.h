#pragma once

#include "Game/AI/AI/aiRailMove.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RemainsFireDroneNormal : public RailMove {
    SEAD_RTTI_OVERRIDE(RemainsFireDroneNormal, RailMove)
public:
    explicit RemainsFireDroneNormal(const InitArg& arg);
    ~RemainsFireDroneNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xa0
    const float* mLightLengthOffset_s{};
    // static_param at offset 0xa8
    const bool* mAdjustRadius_s{};
    // map_unit_param at offset 0xb0
    const int* mSearchLightType_m{};
    // map_unit_param at offset 0xb8
    const float* mLightLength_m{};
    // map_unit_param at offset 0xc0
    const float* mLightRadius_m{};
    // aitree_variable at offset 0xc8
    float* mTargetSpeed_a{};
};

}  // namespace uking::ai
