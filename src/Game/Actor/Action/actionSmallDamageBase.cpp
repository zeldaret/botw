#include "Game/Actor/Action/actionSmallDamageBase.h"

namespace uking::action {

SmallDamageBase::SmallDamageBase(const InitArg& arg) : TakeHitImpactForce(arg) {}

void SmallDamageBase::enter_(ksys::act::ai::InlineParamPack* params) {
    TakeHitImpactForce::enter_(params);
}

void SmallDamageBase::calc_() {
    TakeHitImpactForce::calc_();
}

}  // namespace uking::action
