#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AirOctaFlyUp : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AirOctaFlyUp, ksys::act::ai::Ai)
public:
    explicit AirOctaFlyUp(const InitArg& arg);
    ~AirOctaFlyUp() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mFlyUpDuration_s{};
    // dynamic_param at offset 0x40
    float* mTargetDistance_d{};
    // aitree_variable at offset 0x48
    void* mAirOctaDataMgr_a{};
};

}  // namespace uking::ai
