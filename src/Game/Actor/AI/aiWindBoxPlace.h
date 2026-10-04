#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WindBoxPlace : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WindBoxPlace, ksys::act::ai::Ai)
public:
    explicit WindBoxPlace(const InitArg& arg);
    ~WindBoxPlace() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mRadius_s{};
    // static_param at offset 0x40
    const float* mMaxSpeed_s{};
    // map_unit_param at offset 0x48
    const int* mDirection_m{};
    // map_unit_param at offset 0x50
    const float* mWindSpeed_m{};
};

}  // namespace uking::ai
