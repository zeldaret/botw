#pragma once

#include "Game/AI/AI/aiNavMoveNearTarget.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NavMoveTargetClosestPoint : public NavMoveNearTarget {
    SEAD_RTTI_OVERRIDE(NavMoveTargetClosestPoint, NavMoveNearTarget)
public:
    explicit NavMoveTargetClosestPoint(const InitArg& arg);
    ~NavMoveTargetClosestPoint() override;

    void loadParams_() override;

protected:
    // static_param at offset 0x3a0
    const float* mSearchRadius_s{};
};

}  // namespace uking::ai
