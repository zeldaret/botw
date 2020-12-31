#pragma once

#include "Game/AI/AI/aiNavMoveTarget.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NavMoveNearTarget : public NavMoveTarget {
    SEAD_RTTI_OVERRIDE(NavMoveNearTarget, NavMoveTarget)
public:
    explicit NavMoveNearTarget(const InitArg& arg);
    ~NavMoveNearTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x380
    const float* mTargetVMax_s{};
    // static_param at offset 0x388
    const float* mTargetVMin_s{};
};

}  // namespace uking::ai
