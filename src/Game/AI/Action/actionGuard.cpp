#include "Game/AI/Action/actionGuard.h"

namespace uking::action {

Guard::Guard(const InitArg& arg) : TakeHitImpactForce(arg) {}

Guard::~Guard() = default;

bool Guard::init_(sead::Heap* heap) {
    return TakeHitImpactForce::init_(heap);
}

void Guard::enter_(ksys::act::ai::InlineParamPack* params) {
    TakeHitImpactForce::enter_(params);
}

void Guard::leave_() {
    TakeHitImpactForce::leave_();
}

void Guard::loadParams_() {
    TakeHitImpactForce::loadParams_();
    getStaticParam(&mRotSubsAngRate_s, "RotSubsAngRate");
}

void Guard::calc_() {
    TakeHitImpactForce::calc_();
}

}  // namespace uking::action
