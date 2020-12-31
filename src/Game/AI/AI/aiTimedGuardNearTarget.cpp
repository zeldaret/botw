#include "Game/AI/AI/aiTimedGuardNearTarget.h"

namespace uking::ai {

TimedGuardNearTarget::TimedGuardNearTarget(const InitArg& arg) : GuardNearTarget(arg) {}

TimedGuardNearTarget::~TimedGuardNearTarget() = default;

bool TimedGuardNearTarget::init_(sead::Heap* heap) {
    return GuardNearTarget::init_(heap);
}

void TimedGuardNearTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardNearTarget::enter_(params);
}

void TimedGuardNearTarget::leave_() {
    GuardNearTarget::leave_();
}

void TimedGuardNearTarget::loadParams_() {
    GuardNearTarget::loadParams_();
    getStaticParam(&mGuardEndTime_s, "GuardEndTime");
    getStaticParam(&mGuardStartAngle_s, "GuardStartAngle");
    getStaticParam(&mGuardEndAngle_s, "GuardEndAngle");
}

}  // namespace uking::ai
