#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HorseCheckLineOfSightSelectorBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(HorseCheckLineOfSightSelectorBase, ksys::act::ai::Ai)
public:
    explicit HorseCheckLineOfSightSelectorBase(const InitArg& arg);
    ~HorseCheckLineOfSightSelectorBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mDirectionNum_s{};
    // static_param at offset 0x40
    const float* mDirectionAngle_s{};
    // static_param at offset 0x48
    const float* mDistance_s{};
    // static_param at offset 0x50
    const float* mRadiusScale_s{};
};

}  // namespace uking::ai
