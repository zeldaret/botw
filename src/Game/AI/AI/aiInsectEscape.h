#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class InsectEscape : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(InsectEscape, ksys::act::ai::Ai)
public:
    explicit InsectEscape(const InitArg& arg);
    ~InsectEscape() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mRunAwayDistanceMax_s{};
    // static_param at offset 0x40
    const float* mRunAwayDistanceMin_s{};
    // static_param at offset 0x48
    const float* mRunAwayHeightOffset_s{};
    // static_param at offset 0x50
    const float* mAllowRandAngleVertical_s{};
    // static_param at offset 0x58
    const float* mAllowRandAngleHorizontal_s{};
    // static_param at offset 0x60
    const bool* mInWater_s{};
    // dynamic_param at offset 0x68
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
