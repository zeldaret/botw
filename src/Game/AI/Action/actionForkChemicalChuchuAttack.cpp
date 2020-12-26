#include "Game/AI/Action/actionForkChemicalChuchuAttack.h"

namespace uking::action {

ForkChemicalChuchuAttack::ForkChemicalChuchuAttack(const InitArg& arg)
    : ForkNoWeaponAttackAllTime(arg) {}

ForkChemicalChuchuAttack::~ForkChemicalChuchuAttack() = default;

bool ForkChemicalChuchuAttack::init_(sead::Heap* heap) {
    return ForkNoWeaponAttackAllTime::init_(heap);
}

void ForkChemicalChuchuAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkNoWeaponAttackAllTime::enter_(params);
}

void ForkChemicalChuchuAttack::leave_() {
    ForkNoWeaponAttackAllTime::leave_();
}

void ForkChemicalChuchuAttack::loadParams_() {
    ForkNoWeaponAttackAllTime::loadParams_();
    getStaticParam(&mLandAtkTime_s, "LandAtkTime");
    getStaticParam(&mLandAtkRadius_s, "LandAtkRadius");
}

void ForkChemicalChuchuAttack::calc_() {
    ForkNoWeaponAttackAllTime::calc_();
}

}  // namespace uking::action
