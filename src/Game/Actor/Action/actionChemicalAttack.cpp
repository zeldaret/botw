#include "Game/Actor/Action/actionChemicalAttack.h"

namespace uking::action {

ChemicalAttack::ChemicalAttack(const InitArg& arg) : EmitAttackBase(arg) {}

ChemicalAttack::~ChemicalAttack() = default;

bool ChemicalAttack::init_(sead::Heap* heap) {
    return EmitAttackBase::init_(heap);
}

void ChemicalAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    EmitAttackBase::enter_(params);
}

void ChemicalAttack::leave_() {
    EmitAttackBase::leave_();
}

void ChemicalAttack::loadParams_() {
    EmitAttackBase::loadParams_();
    getStaticParam(&mIsUseMyRange_s, "IsUseMyRange");
    getStaticParam(&mAttackType_s, "AttackType");
}

void ChemicalAttack::calc_() {
    EmitAttackBase::calc_();
}

}  // namespace uking::action
