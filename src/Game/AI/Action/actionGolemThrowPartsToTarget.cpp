#include "Game/AI/Action/actionGolemThrowPartsToTarget.h"

namespace uking::action {

GolemThrowPartsToTarget::GolemThrowPartsToTarget(const InitArg& arg)
    : GolemThrowPartsToTargetBase(arg) {}

GolemThrowPartsToTarget::~GolemThrowPartsToTarget() = default;

bool GolemThrowPartsToTarget::init_(sead::Heap* heap) {
    return GolemThrowPartsToTargetBase::init_(heap);
}

void GolemThrowPartsToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    GolemThrowPartsToTargetBase::enter_(params);
}

void GolemThrowPartsToTarget::leave_() {
    GolemThrowPartsToTargetBase::leave_();
}

void GolemThrowPartsToTarget::loadParams_() {
    GolemThrowPartsToTargetBase::loadParams_();
    getStaticParam(&mShootPitchMin_s, "ShootPitchMin");
    getStaticParam(&mShootPitchMax_s, "ShootPitchMax");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void GolemThrowPartsToTarget::calc_() {
    GolemThrowPartsToTargetBase::calc_();
}

}  // namespace uking::action
