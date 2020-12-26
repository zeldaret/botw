#include "Game/AI/Action/actionForkSwarmAttack.h"

namespace uking::action {

ForkSwarmAttack::ForkSwarmAttack(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkSwarmAttack::~ForkSwarmAttack() = default;

bool ForkSwarmAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkSwarmAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkSwarmAttack::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkSwarmAttack::loadParams_() {
    getStaticParam(&mAttackIntensity_s, "AttackIntensity");
    getStaticParam(&mIsAttackOnce_s, "IsAttackOnce");
}

void ForkSwarmAttack::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
