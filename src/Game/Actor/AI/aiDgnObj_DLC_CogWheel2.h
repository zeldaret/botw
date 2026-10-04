#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DgnObj_DLC_CogWheel2 : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DgnObj_DLC_CogWheel2, ksys::act::ai::Ai)
public:
    explicit DgnObj_DLC_CogWheel2(const InitArg& arg);
    ~DgnObj_DLC_CogWheel2() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // FIXME: remove this
    u8 pad_0x38[0x28];
    // static_param at offset 0x60
    const bool* mCorrectConstraint_s{};
    // map_unit_param at offset 0x68
    const float* mGearRatio_m{};
    // map_unit_param at offset 0x70
    const bool* mRegistFromBeginning_m{};
    // map_unit_param at offset 0x78
    const bool* mJoinSystemGroup_m{};
    // aitree_variable at offset 0x80
    float* mRotationOffset_a{};
};

}  // namespace uking::ai
