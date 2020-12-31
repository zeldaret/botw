#include "Game/AI/AI/aiGolemRoot.h"

namespace uking::ai {

GolemRoot::GolemRoot(const InitArg& arg) : GolemRootBase(arg) {}

GolemRoot::~GolemRoot() = default;

bool GolemRoot::init_(sead::Heap* heap) {
    return GolemRootBase::init_(heap);
}

void GolemRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    GolemRootBase::enter_(params);
}

void GolemRoot::leave_() {
    GolemRootBase::leave_();
}

void GolemRoot::loadParams_() {
    GolemRootBase::loadParams_();
    getStaticParam(&mClimbFinishTime_s, "ClimbFinishTime");
    getStaticParam(&mStandContactHeight_s, "StandContactHeight");
    getStaticParam(&mIsBreakContactTree_s, "IsBreakContactTree");
    getMapUnitParam(&mGolemWeakPointLocation_m, "GolemWeakPointLocation");
    getMapUnitParam(&mGolemSleepType_m, "GolemSleepType");
    getMapUnitParam(&mGolemWeakPointActor_m, "GolemWeakPointActor");
    getAITreeVariable(&mGolemClimbedTime_a, "GolemClimbedTime");
}

}  // namespace uking::ai
