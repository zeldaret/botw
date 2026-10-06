#pragma once

#include "Game/Actor/AI/aiInvincibleNearTargetBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class InvincibleNearTarget : public InvincibleNearTargetBase {
    SEAD_RTTI_OVERRIDE(InvincibleNearTarget, InvincibleNearTargetBase)
public:
    explicit InvincibleNearTarget(const InitArg& arg);
    ~InvincibleNearTarget() override;

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
