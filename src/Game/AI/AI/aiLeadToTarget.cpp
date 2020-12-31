#include "Game/AI/AI/aiLeadToTarget.h"

namespace uking::ai {

LeadToTarget::LeadToTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LeadToTarget::~LeadToTarget() = default;

bool LeadToTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LeadToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LeadToTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LeadToTarget::loadParams_() {
    getStaticParam(&mSuccessRadius_s, "SuccessRadius");
    getStaticParam(&mWaitDistance_s, "WaitDistance");
    getStaticParam(&mResumeLeadDistance_s, "ResumeLeadDistance");
    getStaticParam(&mOkPathFailRange_s, "OkPathFailRange");
    getStaticParam(&mDontWaitIfLeaderIsAhead_s, "DontWaitIfLeaderIsAhead");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mLeaderActor_d, "LeaderActor");
    getStaticParam(&mWaitFramesAfterArrive_s, "WaitFramesAfterArrive");
}

}  // namespace uking::ai
