#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DgnObj_DLC_DungeonRotateTag : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DgnObj_DLC_DungeonRotateTag, ksys::act::ai::Ai)
public:
    explicit DgnObj_DLC_DungeonRotateTag(const InitArg& arg);
    ~DgnObj_DLC_DungeonRotateTag() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const float* mGearRatio_m{};
    // map_unit_param at offset 0x40
    const bool* mRegistFromBeginning_m{};
    // aitree_variable at offset 0x48
    float* mRotationOffset_a{};
};

}  // namespace uking::ai
