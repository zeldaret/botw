#include "Game/AI/Action/actionSiteBossFlyWaitTurnToTarget.h"

namespace uking::action {

SiteBossFlyWaitTurnToTarget::SiteBossFlyWaitTurnToTarget(const InitArg& arg)
    : LastBossFlyWaitTurnToTarget(arg) {}

SiteBossFlyWaitTurnToTarget::~SiteBossFlyWaitTurnToTarget() = default;

bool SiteBossFlyWaitTurnToTarget::init_(sead::Heap* heap) {
    return LastBossFlyWaitTurnToTarget::init_(heap);
}

void SiteBossFlyWaitTurnToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    LastBossFlyWaitTurnToTarget::enter_(params);
}

void SiteBossFlyWaitTurnToTarget::leave_() {
    LastBossFlyWaitTurnToTarget::leave_();
}

void SiteBossFlyWaitTurnToTarget::loadParams_() {
    LastBossFlyWaitTurnToTarget::loadParams_();
}

void SiteBossFlyWaitTurnToTarget::calc_() {
    LastBossFlyWaitTurnToTarget::calc_();
}

}  // namespace uking::action
