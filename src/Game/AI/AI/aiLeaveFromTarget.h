#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LeaveFromTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LeaveFromTarget, ksys::act::ai::Ai)
public:
    explicit LeaveFromTarget(const InitArg& arg);
    ~LeaveFromTarget() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mLeaveDist_s{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
