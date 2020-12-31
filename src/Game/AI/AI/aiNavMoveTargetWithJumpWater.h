#pragma once

#include "Game/AI/AI/aiNavMoveTarget.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NavMoveTargetWithJumpWater : public NavMoveTarget {
    SEAD_RTTI_OVERRIDE(NavMoveTargetWithJumpWater, NavMoveTarget)
public:
    explicit NavMoveTargetWithJumpWater(const InitArg& arg);
    ~NavMoveTargetWithJumpWater() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x380
    const float* mJumpDist_s{};
    // static_param at offset 0x388
    const float* mInWaterDepth_s{};
    // static_param at offset 0x390
    const float* mWaterCheckDist_s{};
    // static_param at offset 0x398
    const bool* mIsCheckDamage_s{};
};

}  // namespace uking::ai
