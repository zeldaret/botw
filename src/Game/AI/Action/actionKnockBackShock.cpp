#include "Game/AI/Action/actionKnockBackShock.h"

namespace uking::action {

KnockBackShock::KnockBackShock(const InitArg& arg) : ksys::act::ai::Action(arg) {}

KnockBackShock::~KnockBackShock() = default;

bool KnockBackShock::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void KnockBackShock::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void KnockBackShock::leave_() {
    ksys::act::ai::Action::leave_();
}

void KnockBackShock::loadParams_() {
    getStaticParam(&mHitImpactForce_s, "HitImpactForce");
    getStaticParam(&mVelReduce_s, "VelReduce");
    getStaticParam(&mVelReduceOnGround_s, "VelReduceOnGround");
}

void KnockBackShock::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
