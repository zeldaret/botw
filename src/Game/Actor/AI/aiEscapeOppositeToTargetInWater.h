#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EscapeOppositeToTargetInWater : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EscapeOppositeToTargetInWater, ksys::act::ai::Ai)
public:
    explicit EscapeOppositeToTargetInWater(const InitArg& arg);
    ~EscapeOppositeToTargetInWater() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mRunAwayDistanceMax_s{};
    // static_param at offset 0x40
    const float* mAllowRandAngleVertical_s{};
    // static_param at offset 0x48
    const float* mAllowRandAngleHorizontal_s{};
    // static_param at offset 0x50
    const float* mDivePercent_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
