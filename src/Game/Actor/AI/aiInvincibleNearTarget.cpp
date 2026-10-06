#include "Game/Actor/AI/aiInvincibleNearTarget.h"

namespace uking::ai {

InvincibleNearTarget::InvincibleNearTarget(const InitArg& arg) : InvincibleNearTargetBase(arg) {}

InvincibleNearTarget::~InvincibleNearTarget() = default;

bool InvincibleNearTarget::init_(sead::Heap* heap) {
    return InvincibleNearTargetBase::init_(heap);
}

void InvincibleNearTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    InvincibleNearTargetBase::enter_(params);
}

void InvincibleNearTarget::leave_() {
    InvincibleNearTargetBase::leave_();
}

void InvincibleNearTarget::loadParams_() {
    InvincibleNearTargetBase::loadParams_();
    getStaticParam(&mGuardEndTime_s, "GuardEndTime");
    getStaticParam(&mGuardStartAngle_s, "GuardStartAngle");
    getStaticParam(&mGuardEndAngle_s, "GuardEndAngle");
}

}  // namespace uking::ai
