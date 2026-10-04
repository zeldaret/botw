#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AnimalLineOfSightSelector : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AnimalLineOfSightSelector, ksys::act::ai::Ai)
public:
    explicit AnimalLineOfSightSelector(const InitArg& arg);
    ~AnimalLineOfSightSelector() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mStartGear_s{};
    // static_param at offset 0x40
    const int* mMinGear_s{};
    // static_param at offset 0x48
    const int* mMaxGear_s{};
    // static_param at offset 0x50
    const float* mGearUpRestrictionFrames_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
