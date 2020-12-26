#include "Game/AI/Action/actionSmallDamageBackwardBase.h"

namespace uking::action {

SmallDamageBackwardBase::SmallDamageBackwardBase(const InitArg& arg) : TakeHitImpactForce(arg) {}

SmallDamageBackwardBase::~SmallDamageBackwardBase() = default;

bool SmallDamageBackwardBase::init_(sead::Heap* heap) {
    return TakeHitImpactForce::init_(heap);
}

void SmallDamageBackwardBase::enter_(ksys::act::ai::InlineParamPack* params) {
    TakeHitImpactForce::enter_(params);
}

void SmallDamageBackwardBase::leave_() {
    TakeHitImpactForce::leave_();
}

void SmallDamageBackwardBase::loadParams_() {
    TakeHitImpactForce::loadParams_();
}

void SmallDamageBackwardBase::calc_() {
    TakeHitImpactForce::calc_();
}

}  // namespace uking::action
