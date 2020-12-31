#include "Game/AI/AI/aiWillBallOperated.h"

namespace uking::ai {

WillBallOperated::WillBallOperated(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WillBallOperated::~WillBallOperated() = default;

bool WillBallOperated::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WillBallOperated::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WillBallOperated::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WillBallOperated::loadParams_() {
    getDynamicParam(&mWaitTime_d, "WaitTime");
    getDynamicParam(&mCommand_d, "Command");
    getDynamicParam(&mBasePos_d, "BasePos");
    getDynamicParam(&mTargetActor_d, "TargetActor");
    getStaticParam(&mWarpDist_s, "WarpDist");
    getStaticParam(&mAttakedChangeDist_s, "AttakedChangeDist");
    getStaticParam(&mIsAttackedTimeAffect_s, "IsAttackedTimeAffect");
}

}  // namespace uking::ai
