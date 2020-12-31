#pragma once

#include "Game/AI/AI/aiWaterSurfaceBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WaterSurface : public WaterSurfaceBase {
    SEAD_RTTI_OVERRIDE(WaterSurface, WaterSurfaceBase)
public:
    explicit WaterSurface(const InitArg& arg);
    ~WaterSurface() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x78
    const int* mLinkTagType_s{};
    // map_unit_param at offset 0x80
    const float* mRiseLength_m{};
    // map_unit_param at offset 0x88
    const float* mRiseSpeed_m{};
};

}  // namespace uking::ai
