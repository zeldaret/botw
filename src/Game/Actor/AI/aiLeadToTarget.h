#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LeadToTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LeadToTarget, ksys::act::ai::Ai)
public:
    explicit LeadToTarget(const InitArg& arg);
    ~LeadToTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mSuccessRadius_s{};
    // static_param at offset 0x40
    const float* mWaitDistance_s{};
    // static_param at offset 0x48
    const float* mResumeLeadDistance_s{};
    // static_param at offset 0x50
    const float* mOkPathFailRange_s{};
    // static_param at offset 0x58
    const float* mWaitFramesAfterArrive_s{};
    // static_param at offset 0x60
    const bool* mDontWaitIfLeaderIsAhead_s{};
    // dynamic_param at offset 0x68
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x70
    ksys::act::BaseProcLink* mLeaderActor_d{};
};

}  // namespace uking::ai
