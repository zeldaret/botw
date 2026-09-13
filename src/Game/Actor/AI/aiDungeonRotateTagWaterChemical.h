#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DungeonRotateTagWaterChemical : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DungeonRotateTagWaterChemical, ksys::act::ai::Ai)
public:
    explicit DungeonRotateTagWaterChemical(const InitArg& arg);
    ~DungeonRotateTagWaterChemical() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mSlowDownRotRadAccel_s{};
    // static_param at offset 0x40
    const float* mSlowDownTimer_s{};
    // static_param at offset 0x48
    const float* mRotRadAccel_s{};
    // static_param at offset 0x50
    const float* mReverseDotTh_s{};
};

}  // namespace uking::ai
