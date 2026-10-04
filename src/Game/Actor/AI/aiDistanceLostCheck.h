#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DistanceLostCheck : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DistanceLostCheck, ksys::act::ai::Ai)
public:
    explicit DistanceLostCheck(const InitArg& arg);
    ~DistanceLostCheck() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mLostTimer_s{};
    // static_param at offset 0x40
    const int* mAddAwarenessRangeType_s{};
    // static_param at offset 0x48
    const float* mLostRange_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
