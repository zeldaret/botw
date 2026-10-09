#include "Game/Actor/Action/actionSmallDamageBackwardBase.h"

namespace uking::action {

SmallDamageBackwardBase::SmallDamageBackwardBase(const InitArg& arg)
    : KnockBackHitImpactForce(arg) {}

SmallDamageBackwardBase::~SmallDamageBackwardBase() = default;

bool SmallDamageBackwardBase::init_(sead::Heap* heap) {
    return KnockBackHitImpactForce::init_(heap);
}

void SmallDamageBackwardBase::enter_(ksys::act::ai::InlineParamPack* params) {
    KnockBackHitImpactForce::enter_(params);
}

void SmallDamageBackwardBase::leave_() {
    KnockBackHitImpactForce::leave_();
}

void SmallDamageBackwardBase::loadParams_() {
    KnockBackHitImpactForce::loadParams_();
}

void SmallDamageBackwardBase::calc_() {
    KnockBackHitImpactForce::calc_();
}

}  // namespace uking::action
