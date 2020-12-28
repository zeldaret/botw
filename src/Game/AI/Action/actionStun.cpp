#include "Game/AI/Action/actionStun.h"

namespace uking::action {

Stun::Stun(const InitArg& arg) : ksys::act::ai::Action(arg) {}

Stun::~Stun() = default;

void Stun::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void Stun::leave_() {
    ksys::act::ai::Action::leave_();
}

void Stun::loadParams_() {
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mHitImpactForceSmallSwordS_s, "HitImpactForceSmallSwordS");
    getStaticParam(&mHitImpactForceLargeSwordS_s, "HitImpactForceLargeSwordS");
    getStaticParam(&mHitImpactForceSpearS_s, "HitImpactForceSpearS");
}

void Stun::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
