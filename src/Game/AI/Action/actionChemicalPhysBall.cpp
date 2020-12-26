#include "Game/AI/Action/actionChemicalPhysBall.h"

namespace uking::action {

ChemicalPhysBall::ChemicalPhysBall(const InitArg& arg) : ChemicalAttackBall(arg) {}

ChemicalPhysBall::~ChemicalPhysBall() = default;

bool ChemicalPhysBall::init_(sead::Heap* heap) {
    return ChemicalAttackBall::init_(heap);
}

void ChemicalPhysBall::enter_(ksys::act::ai::InlineParamPack* params) {
    ChemicalAttackBall::enter_(params);
}

void ChemicalPhysBall::leave_() {
    ChemicalAttackBall::leave_();
}

void ChemicalPhysBall::loadParams_() {
    ChemicalAttackBall::loadParams_();
    getStaticParam(&mDeleteTime_s, "DeleteTime");
}

void ChemicalPhysBall::calc_() {
    ChemicalAttackBall::calc_();
}

}  // namespace uking::action
