#include "Game/AI/AI/aiNavMoveTargetClosestPoint.h"

namespace uking::ai {

NavMoveTargetClosestPoint::NavMoveTargetClosestPoint(const InitArg& arg) : NavMoveNearTarget(arg) {}

NavMoveTargetClosestPoint::~NavMoveTargetClosestPoint() = default;

void NavMoveTargetClosestPoint::loadParams_() {
    NavMoveNearTarget::loadParams_();
    getStaticParam(&mSearchRadius_s, "SearchRadius");
}

}  // namespace uking::ai
