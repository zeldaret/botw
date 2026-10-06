#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CheckLineOfSightSelector : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(CheckLineOfSightSelector, ksys::act::ai::Ai)
public:
    explicit CheckLineOfSightSelector(const InitArg& arg);
    ~CheckLineOfSightSelector() override;

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
