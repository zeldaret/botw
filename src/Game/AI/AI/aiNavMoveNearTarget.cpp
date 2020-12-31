#include "Game/AI/AI/aiNavMoveNearTarget.h"

namespace uking::ai {

NavMoveNearTarget::NavMoveNearTarget(const InitArg& arg) : NavMoveTarget(arg) {}

NavMoveNearTarget::~NavMoveNearTarget() = default;

bool NavMoveNearTarget::init_(sead::Heap* heap) {
    return NavMoveTarget::init_(heap);
}

void NavMoveNearTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    NavMoveTarget::enter_(params);
}

void NavMoveNearTarget::leave_() {
    NavMoveTarget::leave_();
}

void NavMoveNearTarget::loadParams_() {
    NavMoveTarget::loadParams_();
    getStaticParam(&mTargetVMax_s, "TargetVMax");
    getStaticParam(&mTargetVMin_s, "TargetVMin");
}

}  // namespace uking::ai
