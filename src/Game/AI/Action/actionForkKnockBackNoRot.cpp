#include "Game/AI/Action/actionForkKnockBackNoRot.h"

namespace uking::action {

ForkKnockBackNoRot::ForkKnockBackNoRot(const InitArg& arg) : SmallDamageBase(arg) {}

ForkKnockBackNoRot::~ForkKnockBackNoRot() = default;

bool ForkKnockBackNoRot::init_(sead::Heap* heap) {
    return SmallDamageBase::init_(heap);
}

void ForkKnockBackNoRot::enter_(ksys::act::ai::InlineParamPack* params) {
    SmallDamageBase::enter_(params);
}

void ForkKnockBackNoRot::leave_() {
    SmallDamageBase::leave_();
}

void ForkKnockBackNoRot::loadParams_() {
    TakeHitImpactForce::loadParams_();
}

void ForkKnockBackNoRot::calc_() {
    SmallDamageBase::calc_();
}

}  // namespace uking::action
