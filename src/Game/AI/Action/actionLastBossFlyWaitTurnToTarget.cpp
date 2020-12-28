#include "Game/AI/Action/actionLastBossFlyWaitTurnToTarget.h"

namespace uking::action {

LastBossFlyWaitTurnToTarget::LastBossFlyWaitTurnToTarget(const InitArg& arg)
    : LastBossFlyWait(arg) {}

LastBossFlyWaitTurnToTarget::~LastBossFlyWaitTurnToTarget() = default;

void LastBossFlyWaitTurnToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    LastBossFlyWait::enter_(params);
}

void LastBossFlyWaitTurnToTarget::leave_() {
    LastBossFlyWait::leave_();
}

void LastBossFlyWaitTurnToTarget::loadParams_() {
    LastBossFlyWait::loadParams_();
    getStaticParam(&mTurnStartDiffAng_s, "TurnStartDiffAng");
    getStaticParam(&mTurnRate_s, "TurnRate");
    getStaticParam(&mTurnASName_s, "TurnASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::action
