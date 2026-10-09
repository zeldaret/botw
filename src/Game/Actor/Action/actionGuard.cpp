#include "Game/Actor/Action/actionGuard.h"

namespace uking::action {

Guard::Guard(const InitArg& arg) : KnockBackHitImpactForce(arg) {}

void Guard::enter_(ksys::act::ai::InlineParamPack* params) {
    KnockBackHitImpactForce::enter_(params);
}

void Guard::loadParams_() {
    KnockBackHitImpactForce::loadParams_();
    getStaticParam(&mRotSubsAngRate_s, "RotSubsAngRate");
}

void Guard::calc_() {
    KnockBackHitImpactForce::calc_();
}

}  // namespace uking::action
