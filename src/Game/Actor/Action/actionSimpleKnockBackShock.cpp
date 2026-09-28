#include "Game/Actor/Action/actionSimpleKnockBackShock.h"

namespace uking::action {

SimpleKnockBackShock::SimpleKnockBackShock(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SimpleKnockBackShock::~SimpleKnockBackShock() = default;

bool SimpleKnockBackShock::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SimpleKnockBackShock::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SimpleKnockBackShock::leave_() {
    ksys::act::ai::Action::leave_();
}

void SimpleKnockBackShock::loadParams_() {
    getStaticParam(&mHitImpactForce_s, "HitImpactForce");
    getStaticParam(&mVelReduce_s, "VelReduce");
    getStaticParam(&mVelReduceOnGround_s, "VelReduceOnGround");
}

void SimpleKnockBackShock::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
