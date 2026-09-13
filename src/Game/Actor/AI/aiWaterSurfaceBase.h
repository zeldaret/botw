#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WaterSurfaceBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WaterSurfaceBase, ksys::act::ai::Ai)
public:
    explicit WaterSurfaceBase(const InitArg& arg);
    ~WaterSurfaceBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const float* mFlowSpeedFactor_m{};
};

}  // namespace uking::ai
