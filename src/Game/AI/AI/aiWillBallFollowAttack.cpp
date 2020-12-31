#include "Game/AI/AI/aiWillBallFollowAttack.h"

namespace uking::ai {

WillBallFollowAttack::WillBallFollowAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WillBallFollowAttack::~WillBallFollowAttack() = default;

bool WillBallFollowAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WillBallFollowAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WillBallFollowAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WillBallFollowAttack::loadParams_() {
    getStaticParam(&mImmidiateLightningTime_s, "ImmidiateLightningTime");
    getStaticParam(&mCycleY_s, "CycleY");
    getStaticParam(&mDelayTimer_s, "DelayTimer");
    getStaticParam(&mImmidiateLightningXZ_s, "ImmidiateLightningXZ");
    getStaticParam(&mImmidiateLightningY_s, "ImmidiateLightningY");
    getStaticParam(&mAmplitudeY_s, "AmplitudeY");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mCenterPos_d, "CenterPos");
}

}  // namespace uking::ai
