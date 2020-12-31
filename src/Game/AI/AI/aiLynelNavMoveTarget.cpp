#include "Game/AI/AI/aiLynelNavMoveTarget.h"

namespace uking::ai {

LynelNavMoveTarget::LynelNavMoveTarget(const InitArg& arg) : LynelNavMoveNoStop(arg) {}

LynelNavMoveTarget::~LynelNavMoveTarget() = default;

bool LynelNavMoveTarget::init_(sead::Heap* heap) {
    return LynelNavMoveNoStop::init_(heap);
}

void LynelNavMoveTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    LynelNavMoveNoStop::enter_(params);
}

void LynelNavMoveTarget::leave_() {
    LynelNavMoveNoStop::leave_();
}

void LynelNavMoveTarget::loadParams_() {
    LynelNavMoveNoStop::loadParams_();
    getStaticParam(&mStopGear_s, "StopGear");
    getStaticParam(&mCliffCheckDist_s, "CliffCheckDist");
}

}  // namespace uking::ai
