#include "Game/AI/AI/aiLeaveFromTarget.h"

namespace uking::ai {

LeaveFromTarget::LeaveFromTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LeaveFromTarget::~LeaveFromTarget() = default;

void LeaveFromTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LeaveFromTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LeaveFromTarget::loadParams_() {
    getStaticParam(&mLeaveDist_s, "LeaveDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
