#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WaitNearTargetAwarenessRange : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WaitNearTargetAwarenessRange, ksys::act::ai::Ai)
public:
    explicit WaitNearTargetAwarenessRange(const InitArg& arg);
    ~WaitNearTargetAwarenessRange() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mAddAwarenessRangeType_s{};
    // static_param at offset 0x40
    const float* mStartCloseDist_s{};
    // static_param at offset 0x48
    const float* mOutDist_s{};
    // static_param at offset 0x50
    const float* mEndCloseDist_s{};
    // static_param at offset 0x58
    const bool* mUseNavMeshRequest_s{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
