#include "Game/AI/AI/aiNPCRunaway.h"

namespace uking::ai {

NPCRunaway::NPCRunaway(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCRunaway::~NPCRunaway() = default;

bool NPCRunaway::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NPCRunaway::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCRunaway::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NPCRunaway::loadParams_() {
    getStaticParam(&mReleaseDistance_s, "ReleaseDistance");
    getStaticParam(&mCorneredDistance_s, "CorneredDistance");
    getStaticParam(&mStandRateTime_s, "StandRateTime");
    getStaticParam(&mStandingTime_s, "StandingTime");
    getDynamicParam(&mTerrorLevel_d, "TerrorLevel");
    getDynamicParam(&mTerrorLayer_d, "TerrorLayer");
    getDynamicParam(&mIsReturnFromDemo_d, "IsReturnFromDemo");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetVel_d, "TargetVel");
}

}  // namespace uking::ai
