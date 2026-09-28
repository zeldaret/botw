#include "Game/Actor/Action/actionSmallDamageBase.h"

namespace uking::action {

SmallDamageBase::SmallDamageBase(const InitArg& arg) : KnockBackHitImpactForce(arg) {}

void SmallDamageBase::enter_(ksys::act::ai::InlineParamPack* params) {
    KnockBackHitImpactForce::enter_(params);
}

void SmallDamageBase::calc_() {
    KnockBackHitImpactForce::calc_();
}

}  // namespace uking::action
