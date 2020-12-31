#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class BoxWaterRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(BoxWaterRoot, ksys::act::ai::Ai)
public:
    explicit BoxWaterRoot(const InitArg& arg);
    ~BoxWaterRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // FIXME: remove this
    u8 pad_0x38[0x38];
    // map_unit_param at offset 0x70
    const int* mWaterMaterial_m{};
    // map_unit_param at offset 0x78
    const float* mFlowSpeedFactor_m{};
    // map_unit_param at offset 0x80
    const float* mWaterfallRadius_m{};
    // map_unit_param at offset 0x88
    const float* mWaterfallLength_m{};
    // map_unit_param at offset 0x90
    const float* mWaterfallThickness_m{};
    // map_unit_param at offset 0x98
    const float* mWaterfallAngle_m{};
    // map_unit_param at offset 0xa0
    const int* mSoundInDoorType_m{};
};

}  // namespace uking::ai
