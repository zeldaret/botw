#include "Game/AI/Action/actionChemicalAttack.h"

namespace uking::action {

ChemicalAttack::ChemicalAttack(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ChemicalAttack::~ChemicalAttack() = default;

bool ChemicalAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ChemicalAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ChemicalAttack::leave_() {
    ksys::act::ai::Action::leave_();
}

void ChemicalAttack::loadParams_() {
    getStaticParam(&mAttackIntensity_s, "AttackIntensity");
    getStaticParam(&mAttackMinPower_s, "AttackMinPower");
    getMapUnitParam(&mAttackPower_m, "AttackPower");
    getMapUnitParam(&mAttackPowerForPlayer_m, "AttackPowerForPlayer");
    getMapUnitParam(&mScaleTime_m, "ScaleTime");
    getMapUnitParam(&mRange_m, "Range");
    getMapUnitParam(&mRigidBodyName_m, "RigidBodyName");
}

void ChemicalAttack::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
