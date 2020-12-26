#include "Game/AI/Action/actionForkNoWeaponAttackAllTimeMinSet.h"

namespace uking::action {

ForkNoWeaponAttackAllTimeMinSet::ForkNoWeaponAttackAllTimeMinSet(const InitArg& arg)
    : ForkNoWeaponAttackAllTime(arg) {}

ForkNoWeaponAttackAllTimeMinSet::~ForkNoWeaponAttackAllTimeMinSet() = default;

bool ForkNoWeaponAttackAllTimeMinSet::init_(sead::Heap* heap) {
    return ForkNoWeaponAttackAllTime::init_(heap);
}

void ForkNoWeaponAttackAllTimeMinSet::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkNoWeaponAttackAllTime::enter_(params);
}

void ForkNoWeaponAttackAllTimeMinSet::leave_() {
    ForkNoWeaponAttackAllTime::leave_();
}

void ForkNoWeaponAttackAllTimeMinSet::loadParams_() {
    ForkNoWeaponAttackAllTime::loadParams_();
    getStaticParam(&mMinDamage_s, "MinDamage");
}

void ForkNoWeaponAttackAllTimeMinSet::calc_() {
    ForkNoWeaponAttackAllTime::calc_();
}

}  // namespace uking::action
