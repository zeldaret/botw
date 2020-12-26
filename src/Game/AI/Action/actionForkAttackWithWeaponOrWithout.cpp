#include "Game/AI/Action/actionForkAttackWithWeaponOrWithout.h"

namespace uking::action {

ForkAttackWithWeaponOrWithout::ForkAttackWithWeaponOrWithout(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkAttackWithWeaponOrWithout::~ForkAttackWithWeaponOrWithout() = default;

bool ForkAttackWithWeaponOrWithout::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkAttackWithWeaponOrWithout::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkAttackWithWeaponOrWithout::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkAttackWithWeaponOrWithout::loadParams_() {
    getStaticParam(&mAttackIntensity_s, "AttackIntensity");
    getStaticParam(&mIsGuardPierce_s, "IsGuardPierce");
    getStaticParam(&mIsForceGuardBreak_s, "IsForceGuardBreak");
    getStaticParam(&mIsIniviciblePierce_s, "IsIniviciblePierce");
    getStaticParam(&mIsHeavy_s, "IsHeavy");
    getStaticParam(&mIsHammer_s, "IsHammer");
}

void ForkAttackWithWeaponOrWithout::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
