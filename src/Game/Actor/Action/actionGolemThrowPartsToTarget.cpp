#include "Game/Actor/Action/actionGolemThrowPartsToTarget.h"

namespace uking::action {

GolemThrowPartsToTarget::GolemThrowPartsToTarget(const InitArg& arg) : GolemThrowPartsBase(arg) {}

GolemThrowPartsToTarget::~GolemThrowPartsToTarget() = default;

bool GolemThrowPartsToTarget::init_(sead::Heap* heap) {
    return GolemThrowPartsBase::init_(heap);
}

void GolemThrowPartsToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    GolemThrowPartsBase::enter_(params);
}

void GolemThrowPartsToTarget::leave_() {
    GolemThrowPartsBase::leave_();
}

void GolemThrowPartsToTarget::loadParams_() {
    GolemThrowPartsBase::loadParams_();
    getStaticParam(&mShootPitchMin_s, "ShootPitchMin");
    getStaticParam(&mShootPitchMax_s, "ShootPitchMax");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void GolemThrowPartsToTarget::calc_() {
    GolemThrowPartsBase::calc_();
}

}  // namespace uking::action
