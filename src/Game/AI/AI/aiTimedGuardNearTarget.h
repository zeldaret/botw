#pragma once

#include "Game/AI/AI/aiGuardNearTarget.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TimedGuardNearTarget : public GuardNearTarget {
    SEAD_RTTI_OVERRIDE(TimedGuardNearTarget, GuardNearTarget)
public:
    explicit TimedGuardNearTarget(const InitArg& arg);
    ~TimedGuardNearTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x88
    const int* mGuardEndTime_s{};
    // static_param at offset 0x90
    const float* mGuardStartAngle_s{};
    // static_param at offset 0x98
    const float* mGuardEndAngle_s{};
};

}  // namespace uking::ai
