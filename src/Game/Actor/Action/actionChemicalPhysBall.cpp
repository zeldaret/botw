#include "Game/Actor/Action/actionChemicalPhysBall.h"

namespace uking::action {

ChemicalPhysBall::ChemicalPhysBall(const InitArg& arg) : ChemicalAttack(arg) {}

ChemicalPhysBall::~ChemicalPhysBall() = default;

bool ChemicalPhysBall::init_(sead::Heap* heap) {
    return ChemicalAttack::init_(heap);
}

void ChemicalPhysBall::enter_(ksys::act::ai::InlineParamPack* params) {
    ChemicalAttack::enter_(params);
}

void ChemicalPhysBall::leave_() {
    ChemicalAttack::leave_();
}

void ChemicalPhysBall::loadParams_() {
    ChemicalAttack::loadParams_();
    getStaticParam(&mDeleteTime_s, "DeleteTime");
}

void ChemicalPhysBall::calc_() {
    ChemicalAttack::calc_();
}

}  // namespace uking::action
